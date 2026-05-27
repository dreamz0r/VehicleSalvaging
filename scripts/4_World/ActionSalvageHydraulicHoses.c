class ActionSalvageHydraulicHosesCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
    }
}

class ActionSalvageHydraulicHoses : ActionVehicleSalvagingBase
{
    void ActionSalvageHydraulicHoses()
    {
        m_CallbackClass = ActionSalvageHydraulicHosesCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Salvage hydraulic hoses";
    }

    override string GetSalvageItemType()
    {
        return VehicleSalvagingConfig.Get().HydraulicHosesItem;
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

        if (GetGame().IsServer() && !VehicleSalvagingConfig.Get().EnableHydraulicHosesSalvage)
            return false;

        if (!itemInHands || itemInHands != item || !VehicleSalvagingConfig.IsConfiguredTool(itemInHands, VehicleSalvagingConfig.Get().HydraulicHosesTool))
            return false;

        if (!target)
            return false;

        Object targetObject = GetTargetWreckObject(target);

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return false;

        if (GetGame().IsServer() && IsWreckOnCooldown(target))
        {
            SendAlreadySearchedMessage(player, GetAlreadySearchedMessage());
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
        return VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("hydraulichoses", target);
    }

    void MarkWreckSalvaged(ActionTarget target)
    {
        VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("hydraulichoses", target);
    }

    bool IsVanillaVehicleWreck(string objType)
    {
        return VehicleSalvagingWrecks.IsHydraulicHosesWreck(objType);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        Object targetObject = GetTargetWreckObject(action_data.m_Target);

        if (!VehicleSalvagingConfig.Get().EnableHydraulicHosesSalvage)
            return;

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return;

        if (IsWreckOnCooldown(action_data.m_Target))
        {
            SendMessageToClient(player, GetAlreadySearchedMessage());
            return;
        }

        MarkWreckSalvaged(action_data.m_Target);

        float chance = Math.RandomFloatInclusive(0.0, 1.0);

        if (chance <= VehicleSalvagingConfig.Get().HydraulicHosesChance)
        {
            string hosesType = VehicleSalvagingConfig.Get().HydraulicHosesItem;
            EntityAI hoses = player.GetInventory().CreateInInventory(hosesType);

            if (!hoses)
            {
                hoses = EntityAI.Cast(GetGame().CreateObjectEx(hosesType, player.GetPosition(), ECE_PLACE_ON_SURFACE));
            }

            if (hoses)
            {
                ApplyRandomHosesHealth(hoses);
                SendMessageToClient(player, GetSalvagedMessage());
            }
            else
            {
                SendMessageToClient(player, GetCreateFailedMessage());
            }
        }
        else
        {
            SendMessageToClient(player, "You found nothing useful.");
        }

        DamageSalvageTool(action_data.m_MainItem);
    }

    void ApplyRandomHosesHealth(EntityAI hoses)
    {
        hoses.SetHealthLevel(VehicleSalvagingConfig.GetRandomPartHealthLevel());
    }

    void SendMessageToClient(PlayerBase player, string message)
    {
        Param1<string> msg = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msg, true, player.GetIdentity());
    }
}
