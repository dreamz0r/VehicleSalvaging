class VehicleSalvagingConfigData
{
    int CooldownSeconds;

    float SparkPlugChance;
    float RadiatorChance;
    float CarBatteryChance;
    float TruckBatteryChance;
    float GlowPlugChance;
    float HelicopterBatteryChance;
    float HydraulicHosesChance;
    float IgniterPlugChance;

    int BestPartHealthLevel;
    int WorstPartHealthLevel;

    bool EnableSparkPlugSalvage;
    bool EnableRadiatorSalvage;
    bool EnableCarBatterySalvage;
    bool EnableTruckBatterySalvage;
    bool EnableGlowPlugSalvage;
    bool EnableHelicopterBatterySalvage;
    bool EnableHydraulicHosesSalvage;
    bool EnableIgniterPlugSalvage;

    string SparkPlugTool;
    string RadiatorTool;
    string CarBatteryTool;
    string TruckBatteryTool;
    string GlowPlugTool;
    string HelicopterBatteryTool;
    string HydraulicHosesTool;
    string IgniterPlugTool;

    string SparkPlugItem;
    string RadiatorItem;
    string CarBatteryItem;
    string TruckBatteryItem;
    string GlowPlugItem;
    string HelicopterBatteryItem;
    string HydraulicHosesItem;
    string IgniterPlugItem;

    void VehicleSalvagingConfigData()
    {
        CooldownSeconds = 7200;

        SparkPlugChance = 0.15;
        RadiatorChance = 0.15;
        CarBatteryChance = 0.15;
        TruckBatteryChance = 0.15;
        GlowPlugChance = 0.15;
        HelicopterBatteryChance = 0.15;
        HydraulicHosesChance = 0.15;
        IgniterPlugChance = 0.15;

        BestPartHealthLevel = 0;
        WorstPartHealthLevel = 4;

        EnableSparkPlugSalvage = true;
        EnableRadiatorSalvage = true;
        EnableCarBatterySalvage = true;
        EnableTruckBatterySalvage = true;
        EnableGlowPlugSalvage = true;
        EnableHelicopterBatterySalvage = true;
        EnableHydraulicHosesSalvage = true;
        EnableIgniterPlugSalvage = true;

        SparkPlugTool = "LugWrench";
        RadiatorTool = "PipeWrench";
        CarBatteryTool = "Pliers";
        TruckBatteryTool = "Pliers";
        GlowPlugTool = "LugWrench";
        HelicopterBatteryTool = "Pliers";
        HydraulicHosesTool = "Wrench";
        IgniterPlugTool = "LugWrench";

        SparkPlugItem = "SparkPlug";
        RadiatorItem = "CarRadiator";
        CarBatteryItem = "CarBattery";
        TruckBatteryItem = "TruckBattery";
        GlowPlugItem = "GlowPlug";
        HelicopterBatteryItem = "ExpansionHelicopterBattery";
        HydraulicHosesItem = "ExpansionHydraulicHoses";
        IgniterPlugItem = "ExpansionIgniterPlug";
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

    static void Set(VehicleSalvagingConfigData config)
    {
        if (!config)
            return;

        m_Config = config;
        Validate();
    }

    static void Load()
    {
        m_Config = new VehicleSalvagingConfigData();

        if (!GetGame().IsServer())
            return;

        EnsureConfigFolder();

        if (FileExist(GetConfigFile()))
        {
            JsonFileLoader<VehicleSalvagingConfigData>.JsonLoadFile(GetConfigFile(), m_Config);
            Validate();
        }

        Save();
    }

    static void Save()
    {
        if (!GetGame().IsServer())
            return;

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
        m_Config.HelicopterBatteryChance = ClampChance(m_Config.HelicopterBatteryChance);
        m_Config.HydraulicHosesChance = ClampChance(m_Config.HydraulicHosesChance);
        m_Config.IgniterPlugChance = ClampChance(m_Config.IgniterPlugChance);

        m_Config.BestPartHealthLevel = ClampHealthLevel(m_Config.BestPartHealthLevel);
        m_Config.WorstPartHealthLevel = ClampHealthLevel(m_Config.WorstPartHealthLevel);

        if (m_Config.BestPartHealthLevel > m_Config.WorstPartHealthLevel)
        {
            int previousBest = m_Config.BestPartHealthLevel;
            m_Config.BestPartHealthLevel = m_Config.WorstPartHealthLevel;
            m_Config.WorstPartHealthLevel = previousBest;
        }

        m_Config.SparkPlugTool = EnsureString(m_Config.SparkPlugTool, "LugWrench");
        m_Config.RadiatorTool = EnsureString(m_Config.RadiatorTool, "PipeWrench");
        m_Config.CarBatteryTool = EnsureString(m_Config.CarBatteryTool, "Pliers");
        m_Config.TruckBatteryTool = EnsureString(m_Config.TruckBatteryTool, "Pliers");
        m_Config.GlowPlugTool = EnsureString(m_Config.GlowPlugTool, "LugWrench");
        m_Config.HelicopterBatteryTool = EnsureString(m_Config.HelicopterBatteryTool, "Pliers");
        m_Config.HydraulicHosesTool = EnsureString(m_Config.HydraulicHosesTool, "Wrench");
        m_Config.IgniterPlugTool = EnsureString(m_Config.IgniterPlugTool, "LugWrench");

        m_Config.SparkPlugItem = EnsureString(m_Config.SparkPlugItem, "SparkPlug");
        m_Config.RadiatorItem = EnsureString(m_Config.RadiatorItem, "CarRadiator");
        m_Config.CarBatteryItem = EnsureString(m_Config.CarBatteryItem, "CarBattery");
        m_Config.TruckBatteryItem = EnsureString(m_Config.TruckBatteryItem, "TruckBattery");
        m_Config.GlowPlugItem = EnsureString(m_Config.GlowPlugItem, "GlowPlug");
        m_Config.HelicopterBatteryItem = EnsureString(m_Config.HelicopterBatteryItem, "ExpansionHelicopterBattery");
        m_Config.HydraulicHosesItem = EnsureString(m_Config.HydraulicHosesItem, "ExpansionHydraulicHoses");
        m_Config.IgniterPlugItem = EnsureString(m_Config.IgniterPlugItem, "ExpansionIgniterPlug");
    }

    protected static string EnsureString(string value, string defaultValue)
    {
        value.TrimInPlace();

        if (value == "")
            return defaultValue;

        return value;
    }

    static bool IsConfiguredTool(ItemBase item, string toolClassName)
    {
        if (!item || toolClassName == "")
            return false;

        return item.IsKindOf(toolClassName);
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
