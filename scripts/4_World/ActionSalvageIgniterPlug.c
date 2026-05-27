class ActionSalvageIgniterPlugCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
    }
}

class ActionSalvageIgniterPlug : ActionVehicleSalvagingBase
{
    void ActionSalvageIgniterPlug()
    {
        m_CallbackClass = ActionSalvageIgniterPlugCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Salvage igniter plug";
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

        if (GetGame().IsServer() && !VehicleSalvagingConfig.Get().EnableIgniterPlugSalvage)
            return false;

        if (!itemInHands || itemInHands != item || !VehicleSalvagingConfig.IsConfiguredTool(itemInHands, VehicleSalvagingConfig.Get().IgniterPlugTool))
            return false;

        if (!target)
            return false;

        Object targetObject = GetTargetWreckObject(target);

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return false;

        if (GetGame().IsServer() && IsWreckOnCooldown(target))
        {
            SendAlreadySearchedMessage(player, "This wreck has already been searched for an igniter plug.");
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
        return VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("igniterplug", target);
    }

    void MarkWreckSalvaged(ActionTarget target)
    {
        VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("igniterplug", target);
    }

    bool IsVanillaVehicleWreck(string objType)
    {
        return VehicleSalvagingWrecks.IsIgniterPlugWreck(objType);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        Object targetObject = GetTargetWreckObject(action_data.m_Target);

        if (!VehicleSalvagingConfig.Get().EnableIgniterPlugSalvage)
            return;

        if (!targetObject || !IsVanillaVehicleWreck(targetObject.GetType()))
            return;

        if (IsWreckOnCooldown(action_data.m_Target))
        {
            SendMessageToClient(player, "This wreck has already been searched for an igniter plug.");
            return;
        }

        MarkWreckSalvaged(action_data.m_Target);

        float chance = Math.RandomFloatInclusive(0.0, 1.0);

        if (chance <= VehicleSalvagingConfig.Get().IgniterPlugChance)
        {
            EntityAI igniterPlug = CreateIgniterPlug(player);

            if (!igniterPlug)
            {
                igniterPlug = EntityAI.Cast(GetGame().CreateObjectEx(VehicleSalvagingConfig.Get().IgniterPlugItem, player.GetPosition(), ECE_PLACE_ON_SURFACE));
            }

            if (igniterPlug)
            {
                ApplyRandomIgniterPlugHealth(igniterPlug);
                SendMessageToClient(player, "You salvaged an igniter plug from the wreck.");
            }
            else
            {
                SendMessageToClient(player, "You found an igniter plug, but it could not be created.");
            }
        }
        else
        {
            SendMessageToClient(player, "You found nothing useful.");
        }

        DamageSalvageTool(action_data.m_MainItem);
    }

    void ApplyRandomIgniterPlugHealth(EntityAI igniterPlug)
    {
        igniterPlug.SetHealthLevel(VehicleSalvagingConfig.GetRandomPartHealthLevel());
    }

    EntityAI CreateIgniterPlug(PlayerBase player)
    {
        return player.GetInventory().CreateInInventory(VehicleSalvagingConfig.Get().IgniterPlugItem);
    }

    void SendMessageToClient(PlayerBase player, string message)
    {
        Param1<string> msg = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msg, true, player.GetIdentity());
    }
}
