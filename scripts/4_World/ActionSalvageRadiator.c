class ActionSalvageRadiatorCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
    }
}

class ActionSalvageRadiator : ActionVehicleSalvagingBase
{
    void ActionSalvageRadiator()
    {
        m_CallbackClass = ActionSalvageRadiatorCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Salvage radiator";
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

        if (!VehicleSalvagingConfig.Get().EnableRadiatorSalvage)
            return false;

        if (!itemInHands || itemInHands != item || !itemInHands.IsKindOf("PipeWrench"))
            return false;

        if (!target)
            return false;

        Object targetObject = GetTargetWreckObject(target);

        if (targetObject && IsVanillaVehicleWreck(targetObject.GetType()))
            return true;

        return false;
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
        return VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("radiator", target);
    }

    void MarkWreckSalvaged(ActionTarget target)
    {
        VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("radiator", target);
    }

    bool IsVanillaVehicleWreck(string objType)
    {
        return VehicleSalvagingWrecks.IsRadiatorWreck(objType);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        Object targetObject = GetTargetWreckObject(action_data.m_Target);

        if (!VehicleSalvagingConfig.Get().EnableRadiatorSalvage)
            return;

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return;

        if (IsWreckOnCooldown(action_data.m_Target))
        {
            SendMessageToClient(player, "This wreck has already had its radiator searched recently.");
            return;
        }

        MarkWreckSalvaged(action_data.m_Target);

        // 15% chance to find a radiator
        float chance = Math.RandomFloatInclusive(0.0, 1.0);

        if (chance <= VehicleSalvagingConfig.Get().RadiatorChance)
        {
            EntityAI radiator = player.GetInventory().CreateInInventory("CarRadiator");

            if (!radiator)
            {
                radiator = EntityAI.Cast(GetGame().CreateObjectEx("CarRadiator", player.GetPosition(), ECE_PLACE_ON_SURFACE));
            }

            if (radiator)
            {
                ApplyRandomRadiatorHealth(radiator);
                SendMessageToClient(player, "You salvaged a radiator from the wreck.");
            }
            else
            {
                SendMessageToClient(player, "You found a radiator, but it could not be created.");
            }
        }
        else
        {
            SendMessageToClient(player, "You found nothing useful.");
        }

        DamageSalvageTool(action_data.m_MainItem);
    }

    void ApplyRandomRadiatorHealth(EntityAI radiator)
    {
        radiator.SetHealthLevel(VehicleSalvagingConfig.GetRandomPartHealthLevel());
    }

    void SendMessageToClient(PlayerBase player, string message)
    {
        Param1<string> msg = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msg, true, player.GetIdentity());
    }
}
