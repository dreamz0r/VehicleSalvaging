class ActionSalvageTruckBatteryCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
    }
}

class ActionSalvageTruckBattery : ActionVehicleSalvagingBase
{
    void ActionSalvageTruckBattery()
    {
        m_CallbackClass = ActionSalvageTruckBatteryCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Salvage truck battery";
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor(UAMaxDistances.SMALL);
    }

    override bool HasTarget()
    {
        return true;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        ItemBase itemInHands = ItemBase.Cast(player.GetHumanInventory().GetEntityInHands());

        if (GetGame().IsServer() && !VehicleSalvagingConfig.Get().EnableTruckBatterySalvage)
            return false;

        if (!itemInHands || itemInHands != item || !VehicleSalvagingConfig.IsConfiguredTool(itemInHands, VehicleSalvagingConfig.Get().TruckBatteryTool))
            return false;

        if (!target)
            return false;

        Object targetObject = GetTargetWreckObject(target);

        if (!targetObject || !IsHeavyVehicleWreck(targetObject.GetType()))
            return false;

        if (GetGame().IsServer() && IsWreckOnCooldown(target))
        {
            SendAlreadySearchedMessage(player, "This wreck has already been searched for a truck battery.");
            return false;
        }

        return true;
    }

    Object GetTargetWreckObject(ActionTarget target)
    {
        if (!target)
            return null;

        Object targetObject = target.GetObject();

        if (!targetObject)
            targetObject = target.GetParent();

        return targetObject;
    }

    bool IsWreckOnCooldown(ActionTarget target)
    {
        return VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("truckbattery", target);
    }

    void MarkWreckSalvaged(ActionTarget target)
    {
        VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("truckbattery", target);
    }

    bool IsHeavyVehicleWreck(string objType)
    {
        return VehicleSalvagingWrecks.IsTruckBatteryWreck(objType);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        Object targetObject = GetTargetWreckObject(action_data.m_Target);

        if (!VehicleSalvagingConfig.Get().EnableTruckBatterySalvage)
            return;

        if (!targetObject || !IsHeavyVehicleWreck(targetObject.GetType()))
            return;

        if (IsWreckOnCooldown(action_data.m_Target))
        {
            SendMessageToClient(player, "This wreck has already been searched for a truck battery.");
            return;
        }

        MarkWreckSalvaged(action_data.m_Target);

        // 15% chance to find a truck battery
        float chance = Math.RandomFloatInclusive(0.0, 1.0);

        if (chance <= VehicleSalvagingConfig.Get().TruckBatteryChance)
        {
            string truckBatteryType = VehicleSalvagingConfig.Get().TruckBatteryItem;
            EntityAI truckBattery = player.GetInventory().CreateInInventory(truckBatteryType);

            if (!truckBattery)
            {
                truckBattery = EntityAI.Cast(GetGame().CreateObjectEx(truckBatteryType, player.GetPosition(), ECE_PLACE_ON_SURFACE));
            }

            if (truckBattery)
            {
                ApplyRandomTruckBatteryHealth(truckBattery);
                SendMessageToClient(player, "You salvaged a truck battery from the wreck.");
            }
            else
            {
                SendMessageToClient(player, "You found a truck battery, but it could not be created.");
            }
        }
        else
        {
            SendMessageToClient(player, "You found nothing useful.");
        }

        DamageSalvageTool(action_data.m_MainItem);
    }

    void ApplyRandomTruckBatteryHealth(EntityAI truckBattery)
    {
        truckBattery.SetHealthLevel(VehicleSalvagingConfig.GetRandomPartHealthLevel());
    }

    void SendMessageToClient(PlayerBase player, string message)
    {
        Param1<string> msg = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msg, true, player.GetIdentity());
    }
}
