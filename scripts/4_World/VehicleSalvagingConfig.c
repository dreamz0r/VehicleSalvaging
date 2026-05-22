class VehicleSalvagingConfigData
{
    int CooldownSeconds;

    float SparkPlugChance;
    float RadiatorChance;
    float CarBatteryChance;
    float TruckBatteryChance;
    float GlowPlugChance;

    int BestPartHealthLevel;
    int WorstPartHealthLevel;

    bool EnableSparkPlugSalvage;
    bool EnableRadiatorSalvage;
    bool EnableCarBatterySalvage;
    bool EnableTruckBatterySalvage;
    bool EnableGlowPlugSalvage;

    void VehicleSalvagingConfigData()
    {
        CooldownSeconds = 7200;

        SparkPlugChance = 0.15;
        RadiatorChance = 0.15;
        CarBatteryChance = 0.15;
        TruckBatteryChance = 0.15;
        GlowPlugChance = 0.15;

        BestPartHealthLevel = 0;
        WorstPartHealthLevel = 4;

        EnableSparkPlugSalvage = true;
        EnableRadiatorSalvage = true;
        EnableCarBatterySalvage = true;
        EnableTruckBatterySalvage = true;
        EnableGlowPlugSalvage = true;
    }
}

class VehicleSalvagingConfig
{
    protected static ref VehicleSalvagingConfigData m_Config;

    static VehicleSalvagingConfigData Get()
    {
        if (!m_Config)
            Load();

        return m_Config;
    }

    static void Load()
    {
        EnsureConfigFolder();

        m_Config = new VehicleSalvagingConfigData();

        if (FileExist(GetConfigFile()))
        {
            JsonFileLoader<VehicleSalvagingConfigData>.JsonLoadFile(GetConfigFile(), m_Config);
            Validate();
        }

        Save();
    }

    static void Save()
    {
        EnsureConfigFolder();
        JsonFileLoader<VehicleSalvagingConfigData>.JsonSaveFile(GetConfigFile(), m_Config);
    }

    protected static void EnsureConfigFolder()
    {
        if (!FileExist(GetConfigFolder()))
            MakeDirectory(GetConfigFolder());
    }

    protected static string GetConfigFolder()
    {
        return "$profile:VehicleSalvaging";
    }

    protected static string GetConfigFile()
    {
        return "$profile:VehicleSalvaging/VehicleSalvagingConfig.json";
    }

    protected static void Validate()
    {
        if (m_Config.CooldownSeconds < 0)
            m_Config.CooldownSeconds = 7200;

        m_Config.SparkPlugChance = ClampChance(m_Config.SparkPlugChance);
        m_Config.RadiatorChance = ClampChance(m_Config.RadiatorChance);
        m_Config.CarBatteryChance = ClampChance(m_Config.CarBatteryChance);
        m_Config.TruckBatteryChance = ClampChance(m_Config.TruckBatteryChance);
        m_Config.GlowPlugChance = ClampChance(m_Config.GlowPlugChance);

        m_Config.BestPartHealthLevel = ClampHealthLevel(m_Config.BestPartHealthLevel);
        m_Config.WorstPartHealthLevel = ClampHealthLevel(m_Config.WorstPartHealthLevel);

        if (m_Config.BestPartHealthLevel > m_Config.WorstPartHealthLevel)
        {
            int previousBest = m_Config.BestPartHealthLevel;
            m_Config.BestPartHealthLevel = m_Config.WorstPartHealthLevel;
            m_Config.WorstPartHealthLevel = previousBest;
        }
    }

    protected static float ClampChance(float chance)
    {
        if (chance < 0.0)
            return 0.0;

        if (chance > 1.0)
            return 1.0;

        return chance;
    }

    protected static int ClampHealthLevel(int healthLevel)
    {
        if (healthLevel < 0)
            return 0;

        if (healthLevel > 4)
            return 4;

        return healthLevel;
    }

    static int GetRandomPartHealthLevel()
    {
        VehicleSalvagingConfigData config = Get();
        return Math.RandomIntInclusive(config.BestPartHealthLevel, config.WorstPartHealthLevel);
    }
}
