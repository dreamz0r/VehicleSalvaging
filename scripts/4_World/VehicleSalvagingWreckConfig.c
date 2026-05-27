class VehicleSalvagingWreckConfigData
{
    ref array<string> SparkPlugWrecks;
    ref array<string> RadiatorWrecks;
    ref array<string> CarBatteryWrecks;
    ref array<string> TruckBatteryWrecks;
    ref array<string> GlowPlugWrecks;
    ref array<string> HelicopterBatteryWrecks;
    ref array<string> HydraulicHosesWrecks;
    ref array<string> IgniterPlugWrecks;

    void VehicleSalvagingWreckConfigData()
    {
        SparkPlugWrecks = new array<string>();
        RadiatorWrecks = new array<string>();
        CarBatteryWrecks = new array<string>();
        TruckBatteryWrecks = new array<string>();
        GlowPlugWrecks = new array<string>();
        HelicopterBatteryWrecks = new array<string>();
        HydraulicHosesWrecks = new array<string>();
        IgniterPlugWrecks = new array<string>();

        LoadDefaults();
    }

    void LoadDefaults()
    {
        ClearAll();

        AddPassengerGasolineWrecks(SparkPlugWrecks);
        AddPoliceGasolineWrecks(SparkPlugWrecks);

        AddPassengerGasolineWrecks(CarBatteryWrecks);
        AddPoliceGasolineWrecks(CarBatteryWrecks);
        AddLightDieselWrecks(CarBatteryWrecks);
        AddLightVanWrecks(CarBatteryWrecks);

        AddPassengerGasolineWrecks(RadiatorWrecks);
        AddPoliceGasolineWrecks(RadiatorWrecks);
        AddLightDieselWrecks(RadiatorWrecks);
        AddLightVanWrecks(RadiatorWrecks);
        AddHeavyDieselWrecks(RadiatorWrecks);

        AddHeavyDieselWrecks(TruckBatteryWrecks);

        AddLightDieselWrecks(GlowPlugWrecks);
        AddLightVanWrecks(GlowPlugWrecks);
        AddHeavyDieselWrecks(GlowPlugWrecks);

        AddHeliCrashWrecks(HelicopterBatteryWrecks);
        AddHeliCrashWrecks(HydraulicHosesWrecks);
        AddHeliCrashWrecks(IgniterPlugWrecks);
    }

    protected void ClearAll()
    {
        SparkPlugWrecks.Clear();
        RadiatorWrecks.Clear();
        CarBatteryWrecks.Clear();
        TruckBatteryWrecks.Clear();
        GlowPlugWrecks.Clear();
        HelicopterBatteryWrecks.Clear();
        HydraulicHosesWrecks.Clear();
        IgniterPlugWrecks.Clear();
    }

    protected void AddPassengerGasolineWrecks(array<string> wrecks)
    {
        wrecks.Insert("land_wreck_hb01_aban1_blue");
        wrecks.Insert("land_wreck_hb01_aban1_blue_de");
        wrecks.Insert("land_wreck_hb01_aban1_green");
        wrecks.Insert("land_wreck_hb01_aban1_green_de");
        wrecks.Insert("land_wreck_hb01_aban1_white");
        wrecks.Insert("land_wreck_hb01_aban1_white_de");
        wrecks.Insert("land_wreck_hb01_aban2_blue");
        wrecks.Insert("land_wreck_hb01_aban2_blue_de");
        wrecks.Insert("land_wreck_hb01_aban2_green");
        wrecks.Insert("land_wreck_hb01_aban2_green_de");
        wrecks.Insert("land_wreck_hb01_aban2_white");
        wrecks.Insert("land_wreck_hb01_aban2_white_de");
        wrecks.Insert("land_wreck_hb02_aban1_black");
        wrecks.Insert("land_wreck_hb02_aban1_black_de");
        wrecks.Insert("land_wreck_hb02_aban1_blue");
        wrecks.Insert("land_wreck_hb02_aban1_blue_de");
        wrecks.Insert("land_wreck_hb02_aban1_red");
        wrecks.Insert("land_wreck_hb02_aban1_red_de");
        wrecks.Insert("land_wreck_hb02_aban2_black");
        wrecks.Insert("land_wreck_hb02_aban2_black_de");
        wrecks.Insert("land_wreck_hb02_aban2_blue");
        wrecks.Insert("land_wreck_hb02_aban2_blue_de");
        wrecks.Insert("land_wreck_hb02_aban2_red");
        wrecks.Insert("land_wreck_hb02_aban2_red_de");
        wrecks.Insert("land_wreck_lada_green");
        wrecks.Insert("land_wreck_lada_red");
        wrecks.Insert("land_wreck_s1023_beige");
        wrecks.Insert("land_wreck_s1023_blue");
        wrecks.Insert("land_wreck_s1023_medic_beige_de");
        wrecks.Insert("land_wreck_s1023_red");
        wrecks.Insert("land_wreck_sed01_aban1_black");
        wrecks.Insert("land_wreck_sed01_aban1_black_de");
        wrecks.Insert("land_wreck_sed01_aban1_white");
        wrecks.Insert("land_wreck_sed01_aban1_white_de");
        wrecks.Insert("land_wreck_sed01_aban1_wine");
        wrecks.Insert("land_wreck_sed01_aban1_wine_de");
        wrecks.Insert("land_wreck_sed01_aban2_black");
        wrecks.Insert("land_wreck_sed01_aban2_black_de");
        wrecks.Insert("land_wreck_sed01_aban2_white");
        wrecks.Insert("land_wreck_sed01_aban2_white_de");
        wrecks.Insert("land_wreck_sed01_aban2_wine");
        wrecks.Insert("land_wreck_sed01_aban2_wine_de");
        wrecks.Insert("land_wreck_sed02_aban1_grey");
        wrecks.Insert("land_wreck_sed02_aban1_grey_de");
        wrecks.Insert("land_wreck_sed02_aban1_red");
        wrecks.Insert("land_wreck_sed02_aban1_red_de");
        wrecks.Insert("land_wreck_sed02_aban1_yellow");
        wrecks.Insert("land_wreck_sed02_aban1_yellow_de");
        wrecks.Insert("land_wreck_sed02_aban2_grey");
        wrecks.Insert("land_wreck_sed02_aban2_grey_de");
        wrecks.Insert("land_wreck_sed02_aban2_red");
        wrecks.Insert("land_wreck_sed02_aban2_red_de");
        wrecks.Insert("land_wreck_sed02_aban2_yellow");
        wrecks.Insert("land_wreck_sed02_aban2_yellow_de");
        wrecks.Insert("land_wreck_volha_blue");
        wrecks.Insert("land_wreck_volha_grey");
    }

    protected void AddPoliceGasolineWrecks(array<string> wrecks)
    {
        wrecks.Insert("land_wreck_hb01_aban1_police_de");
        wrecks.Insert("land_wreck_hb01_aban2_police_de");
        wrecks.Insert("land_wreck_sed01_aban1_police");
        wrecks.Insert("land_wreck_sed01_aban1_police_de");
        wrecks.Insert("land_wreck_sed01_aban2_police");
        wrecks.Insert("land_wreck_sed01_aban2_police_de");
        wrecks.Insert("land_wreck_volha_police");
    }

    protected void AddLightDieselWrecks(array<string> wrecks)
    {
        wrecks.Insert("land_wreck_offroad02_aban1");
        wrecks.Insert("land_wreck_offroad02_aban1_de");
        wrecks.Insert("land_wreck_offroad02_aban2");
        wrecks.Insert("land_wreck_offroad02_aban2_de");
    }

    protected void AddLightVanWrecks(array<string> wrecks)
    {
        wrecks.Insert("land_wreck_van01_aban1_beige");
        wrecks.Insert("land_wreck_van01_aban1_blue");
        wrecks.Insert("land_wreck_van01_aban2_beige");
        wrecks.Insert("land_wreck_van01_aban2_blue");
    }

    protected void AddHeavyDieselWrecks(array<string> wrecks)
    {
        wrecks.Insert("land_wreck_ikarus");
        wrecks.Insert("land_wreck_ikarus_de");
        wrecks.Insert("land_wreck_tractor_de");
        wrecks.Insert("land_wreck_truck01_aban1_blue");
        wrecks.Insert("land_wreck_truck01_aban1_blue_de");
        wrecks.Insert("land_wreck_truck01_aban1_firetruck");
        wrecks.Insert("land_wreck_truck01_aban1_firetruck_de");
        wrecks.Insert("land_wreck_truck01_aban1_green");
        wrecks.Insert("land_wreck_truck01_aban1_green_de");
        wrecks.Insert("land_wreck_truck01_aban1_orange");
        wrecks.Insert("land_wreck_truck01_aban1_orange_de");
        wrecks.Insert("land_wreck_truck01_aban2_blue");
        wrecks.Insert("land_wreck_truck01_aban2_blue_de");
        wrecks.Insert("land_wreck_truck01_aban2_firetruck");
        wrecks.Insert("land_wreck_truck01_aban2_firetruck_de");
        wrecks.Insert("land_wreck_truck01_aban2_green");
        wrecks.Insert("land_wreck_truck01_aban2_green_de");
        wrecks.Insert("land_wreck_truck01_aban2_orange");
        wrecks.Insert("land_wreck_truck01_aban2_orange_de");
        wrecks.Insert("land_wreck_truck02_aban1_green");
        wrecks.Insert("land_wreck_truck02_aban1_orange");
        wrecks.Insert("land_wreck_truck02_aban2_green");
        wrecks.Insert("land_wreck_truck02_aban2_orange");
        wrecks.Insert("land_wreck_v3s_de");
    }

    protected static void AddHeliCrashWrecks(array<string> wrecks)
    {
        wrecks.Insert("wreck_uh1y");
        wrecks.Insert("wreck_uh1y_de");
        wrecks.Insert("wreck_mi8");
        wrecks.Insert("wreck_mi8_de");
        wrecks.Insert("wreck_mi8_crashed");
        wrecks.Insert("wreck_mi8_crashed_de");
    }
}

class VehicleSalvagingWreckConfig
{
    protected static ref VehicleSalvagingWreckConfigData m_Config;

    static VehicleSalvagingWreckConfigData Get()
    {
        if (!m_Config)
            Load();

        return m_Config;
    }

    static void Load()
    {
        EnsureConfigFolder();

        m_Config = new VehicleSalvagingWreckConfigData();

        if (FileExist(GetConfigFile()))
        {
            JsonFileLoader<VehicleSalvagingWreckConfigData>.JsonLoadFile(GetConfigFile(), m_Config);
            Validate();
        }

        Save();
    }

    static void Save()
    {
        EnsureConfigFolder();
        JsonFileLoader<VehicleSalvagingWreckConfigData>.JsonSaveFile(GetConfigFile(), m_Config);
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
        return "$profile:VehicleSalvaging/VehicleSalvagingWreckConfig.json";
    }

    protected static void Validate()
    {
        if (!m_Config.SparkPlugWrecks)
            m_Config.SparkPlugWrecks = new array<string>();

        if (!m_Config.RadiatorWrecks)
            m_Config.RadiatorWrecks = new array<string>();

        if (!m_Config.CarBatteryWrecks)
            m_Config.CarBatteryWrecks = new array<string>();

        if (!m_Config.TruckBatteryWrecks)
            m_Config.TruckBatteryWrecks = new array<string>();

        if (!m_Config.GlowPlugWrecks)
            m_Config.GlowPlugWrecks = new array<string>();

        if (!m_Config.HelicopterBatteryWrecks)
        {
            m_Config.HelicopterBatteryWrecks = new array<string>();
            AddDefaultHeliCrashWrecks(m_Config.HelicopterBatteryWrecks);
        }

        if (!m_Config.HydraulicHosesWrecks)
        {
            m_Config.HydraulicHosesWrecks = new array<string>();
            AddDefaultHeliCrashWrecks(m_Config.HydraulicHosesWrecks);
        }

        if (!m_Config.IgniterPlugWrecks)
        {
            m_Config.IgniterPlugWrecks = new array<string>();
            AddDefaultHeliCrashWrecks(m_Config.IgniterPlugWrecks);
        }

        NormalizeWreckList(m_Config.SparkPlugWrecks);
        NormalizeWreckList(m_Config.RadiatorWrecks);
        NormalizeWreckList(m_Config.CarBatteryWrecks);
        NormalizeWreckList(m_Config.TruckBatteryWrecks);
        NormalizeWreckList(m_Config.GlowPlugWrecks);
        NormalizeWreckList(m_Config.HelicopterBatteryWrecks);
        NormalizeWreckList(m_Config.HydraulicHosesWrecks);
        NormalizeWreckList(m_Config.IgniterPlugWrecks);

        EnsureDefaultHeliCrashWrecks(m_Config.HelicopterBatteryWrecks);
        EnsureDefaultHeliCrashWrecks(m_Config.HydraulicHosesWrecks);
        EnsureDefaultHeliCrashWrecks(m_Config.IgniterPlugWrecks);
    }

    protected static void NormalizeWreckList(array<string> wrecks)
    {
        for (int i = wrecks.Count() - 1; i >= 0; i--)
        {
            string wreckType = wrecks.Get(i);
            wreckType.TrimInPlace();
            wreckType.ToLower();

            if (wreckType == "")
            {
                wrecks.Remove(i);
            }
            else
            {
                wrecks.Set(i, wreckType);
            }
        }
    }

    protected static void AddDefaultHeliCrashWrecks(array<string> wrecks)
    {
        AddHeliCrashWreckNames(wrecks);
    }

    protected static void EnsureDefaultHeliCrashWrecks(array<string> wrecks)
    {
        EnsureWreckName(wrecks, "wreck_uh1y");
        EnsureWreckName(wrecks, "wreck_uh1y_de");
        EnsureWreckName(wrecks, "wreck_mi8");
        EnsureWreckName(wrecks, "wreck_mi8_de");
        EnsureWreckName(wrecks, "wreck_mi8_crashed");
        EnsureWreckName(wrecks, "wreck_mi8_crashed_de");
    }

    protected static void EnsureWreckName(array<string> wrecks, string wreckType)
    {
        if (!wrecks)
            return;

        for (int i = 0; i < wrecks.Count(); i++)
        {
            if (wrecks.Get(i) == wreckType)
                return;
        }

        wrecks.Insert(wreckType);
    }

    protected static void AddHeliCrashWreckNames(array<string> wrecks)
    {
        wrecks.Insert("wreck_uh1y");
        wrecks.Insert("wreck_uh1y_de");
        wrecks.Insert("wreck_mi8");
        wrecks.Insert("wreck_mi8_de");
        wrecks.Insert("wreck_mi8_crashed");
        wrecks.Insert("wreck_mi8_crashed_de");
    }
}
