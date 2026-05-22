class ActionSalvageGlowPlugCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
    }
}

class ActionSalvageGlowPlug : ActionVehicleSalvagingBase
{
    void ActionSalvageGlowPlug()
    {
        m_CallbackClass = ActionSalvageGlowPlugCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "Salvage glow plug";
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

        if (!VehicleSalvagingConfig.Get().EnableGlowPlugSalvage)
            return false;

        if (!itemInHands || itemInHands != item || !itemInHands.IsKindOf("LugWrench"))
            return false;

        if (!target)
            return false;

        Object targetObject = GetTargetWreckObject(target);

        if (targetObject && IsDieselVehicleWreck(targetObject.GetType()))
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
        return VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("glowplug", target);
    }

    void MarkWreckSalvaged(ActionTarget target)
    {
        VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("glowplug", target);
    }

    bool IsDieselVehicleWreck(string objType)
    {
        return VehicleSalvagingWrecks.IsGlowPlugWreck(objType);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        Object targetObject = GetTargetWreckObject(action_data.m_Target);

        if (!VehicleSalvagingConfig.Get().EnableGlowPlugSalvage)
            return;

        if (!targetObject || !IsDieselVehicleWreck(targetObject.GetType()))
            return;

        if (IsWreckOnCooldown(action_data.m_Target))
        {
            SendMessageToClient(player, "This wreck has already had its glow plug searched recently.");
            return;
        }

        MarkWreckSalvaged(action_data.m_Target);

        // 15% chance to find a glow plug
        float chance = Math.RandomFloatInclusive(0.0, 1.0);

        if (chance <= VehicleSalvagingConfig.Get().GlowPlugChance)
        {
            EntityAI glowPlug = player.GetInventory().CreateInInventory("GlowPlug");

            if (!glowPlug)
            {
                glowPlug = EntityAI.Cast(GetGame().CreateObjectEx("GlowPlug", player.GetPosition(), ECE_PLACE_ON_SURFACE));
            }

            if (glowPlug)
            {
                ApplyRandomGlowPlugHealth(glowPlug);
                SendMessageToClient(player, "You salvaged a glow plug from the wreck.");
            }
            else
            {
                SendMessageToClient(player, "You found a glow plug, but it could not be created.");
            }
        }
        else
        {
            SendMessageToClient(player, "You found nothing useful.");
        }

        DamageSalvageTool(action_data.m_MainItem);
    }

    void ApplyRandomGlowPlugHealth(EntityAI glowPlug)
    {
        glowPlug.SetHealthLevel(VehicleSalvagingConfig.GetRandomPartHealthLevel());
    }

    void SendMessageToClient(PlayerBase player, string message)
    {
        Param1<string> msg = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msg, true, player.GetIdentity());
    }
}
