class ActionVehicleSalvagingBase : ActionContinuousBase
{
    const float TOOL_DAMAGE_FRACTION = 0.10;

    void ActionVehicleSalvagingBase()
    {
        m_LockTargetOnUse = false;
    }

    override bool CanContinue(ActionData action_data)
    {
        if (!action_data || !action_data.m_Player)
            return false;

        if (!action_data.m_Player.IsPlayerInStance(action_data.m_PossibleStanceMask))
            return false;

        if (!m_ConditionItem || !m_ConditionItem.CanContinue(action_data.m_Player, action_data.m_MainItem))
            return false;

        return ActionConditionContinue(action_data);
    }

    void DamageSalvageTool(ItemBase tool)
    {
        if (!tool)
            return;

        float maxHealth = tool.GetMaxHealth("", "");

        if (maxHealth <= 0)
            return;

        float currentHealth = tool.GetHealth("", "");
        float newHealth = currentHealth - (maxHealth * TOOL_DAMAGE_FRACTION);

        if (newHealth < 0)
            newHealth = 0;

        tool.SetHealth("", "", newHealth);
    }
}
