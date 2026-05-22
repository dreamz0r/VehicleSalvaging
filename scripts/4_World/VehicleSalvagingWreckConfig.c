class VehicleSalvagingWreckConfigData
{
    ref array<string> SparkPlugWrecks;
    ref array<string> RadiatorWrecks;
    ref array<string> CarBatteryWrecks;
    ref array<string> TruckBatteryWrecks;
    ref array<string> GlowPlugWrecks;

    void VehicleSalvagingWreckConfigData()
    {
        SparkPlugWrecks = new array<string>();
        RadiatorWrecks = new array<string>();
        CarBatteryWrecks = new array<string>();
        TruckBatteryWrecks = new array<string>();
        GlowPlugWrecks = new array<string>();

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
    }

    protected void ClearAll()
    {
        SparkPlugWrecks.Clear();
        RadiatorWrecks.Clear();
        CarBatteryWrecks.Clear();
        TruckBatteryWrecks.Clear();
        GlowPlugWrecks.Clear();
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

        NormalizeWreckList(m_Config.SparkPlugWrecks);
        NormalizeWreckList(m_Config.RadiatorWrecks);
        NormalizeWreckList(m_Config.CarBatteryWrecks);
        NormalizeWreckList(m_Config.TruckBatteryWrecks);
        NormalizeWreckList(m_Config.GlowPlugWrecks);
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
}
