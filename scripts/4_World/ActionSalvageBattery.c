class ActionSalvageBatteryCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
    }
}

class ActionSalvageBattery : ActionVehicleSalvagingBase
{
    void ActionSalvageBattery()
    {
        m_CallbackClass = ActionSalvageBatteryCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Salvage car battery";
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

        if (!VehicleSalvagingConfig.Get().EnableCarBatterySalvage)
            return false;

        if (!itemInHands || itemInHands != item || !itemInHands.IsKindOf("Pliers"))
            return false;

        if (!target)
            return false;

        Object targetObject = GetTargetWreckObject(target);

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return false;

        if (IsWreckOnCooldown(target))
        {
            SendAlreadySearchedMessage(player, "This wreck has already been searched for a car battery.");
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
        return VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("battery", target);
    }

    void MarkWreckSalvaged(ActionTarget target)
    {
        VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("battery", target);
    }

    bool IsVanillaVehicleWreck(string objType)
    {
        return VehicleSalvagingWrecks.IsCarBatteryWreck(objType);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        Object targetObject = GetTargetWreckObject(action_data.m_Target);

        if (!VehicleSalvagingConfig.Get().EnableCarBatterySalvage)
            return;

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return;

        if (IsWreckOnCooldown(action_data.m_Target))
        {
            SendMessageToClient(player, "This wreck has already been searched for a car battery.");
            return;
        }

        MarkWreckSalvaged(action_data.m_Target);

        // 15% chance to find a car battery
        float chance = Math.RandomFloatInclusive(0.0, 1.0);

        if (chance <= VehicleSalvagingConfig.Get().CarBatteryChance)
        {
            EntityAI battery = player.GetInventory().CreateInInventory("CarBattery");

            if (!battery)
            {
                battery = EntityAI.Cast(GetGame().CreateObjectEx("CarBattery", player.GetPosition(), ECE_PLACE_ON_SURFACE));
            }

            if (battery)
            {
                ApplyRandomBatteryHealth(battery);
                SendMessageToClient(player, "You salvaged a car battery from the wreck.");
            }
            else
            {
                SendMessageToClient(player, "You found a car battery, but it could not be created.");
            }
        }
        else
        {
            SendMessageToClient(player, "You found nothing useful.");
        }

        DamageSalvageTool(action_data.m_MainItem);
    }

    void ApplyRandomBatteryHealth(EntityAI battery)
    {
        battery.SetHealthLevel(VehicleSalvagingConfig.GetRandomPartHealthLevel());
    }

    void SendMessageToClient(PlayerBase player, string message)
    {
        Param1<string> msg = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msg, true, player.GetIdentity());
    }
}
