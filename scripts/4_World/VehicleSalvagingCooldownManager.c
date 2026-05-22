class VehicleSalvagingCooldownEntry
{
    string Key;
    int ExpiresAt;
}

class VehicleSalvagingCooldownStore
{
    ref array<ref VehicleSalvagingCooldownEntry> Cooldowns;

    void VehicleSalvagingCooldownStore()
    {
        Cooldowns = new array<ref VehicleSalvagingCooldownEntry>();
    }
}

class VehicleSalvagingCooldownManager
{
    protected static ref VehicleSalvagingCooldownManager m_Instance;
    protected ref map<string, int> m_Cooldowns;
    protected ref VehicleSalvagingCooldownStore m_Store;

    void VehicleSalvagingCooldownManager()
    {
        m_Cooldowns = new map<string, int>();
        m_Store = new VehicleSalvagingCooldownStore();
        Load();
    }

    static VehicleSalvagingCooldownManager GetInstance()
    {
        if (!m_Instance)
            m_Instance = new VehicleSalvagingCooldownManager();

        return m_Instance;
    }

    bool IsOnCooldown(string partType, ActionTarget target)
    {
        string key = BuildCooldownKey(partType, target);

        if (!m_Cooldowns.Contains(key))
            return false;

        int now = GetCurrentTimeSeconds();
        int expiresAt = m_Cooldowns.Get(key);

        if (now < expiresAt)
            return true;

        m_Cooldowns.Remove(key);
        Save();
        return false;
    }

    void MarkSalvaged(string partType, ActionTarget target)
    {
        int cooldownSeconds = VehicleSalvagingConfig.Get().CooldownSeconds;

        if (cooldownSeconds <= 0)
            return;

        string key = BuildCooldownKey(partType, target);
        m_Cooldowns.Set(key, GetCurrentTimeSeconds() + cooldownSeconds);
        Save();
    }

    void ClearCooldowns()
    {
        EnsureCooldownFolder();
        m_Cooldowns.Clear();

        if (!m_Store)
            m_Store = new VehicleSalvagingCooldownStore();

        if (!m_Store.Cooldowns)
            m_Store.Cooldowns = new array<ref VehicleSalvagingCooldownEntry>();

        m_Store.Cooldowns.Clear();
        JsonFileLoader<VehicleSalvagingCooldownStore>.JsonSaveFile(GetCooldownFile(), m_Store);
    }

    protected void Load()
    {
        EnsureCooldownFolder();

        if (FileExist(GetCooldownFile()))
        {
            JsonFileLoader<VehicleSalvagingCooldownStore>.JsonLoadFile(GetCooldownFile(), m_Store);
        }

        if (!m_Store)
            m_Store = new VehicleSalvagingCooldownStore();

        if (!m_Store.Cooldowns)
        {
            m_Store.Cooldowns = new array<ref VehicleSalvagingCooldownEntry>();
        }

        int now = GetCurrentTimeSeconds();

        for (int i = 0; i < m_Store.Cooldowns.Count(); i++)
        {
            VehicleSalvagingCooldownEntry entry = m_Store.Cooldowns.Get(i);

            if (entry && entry.Key != "" && entry.ExpiresAt > now)
                m_Cooldowns.Set(entry.Key, entry.ExpiresAt);
        }

        Save();
    }

    protected void Save()
    {
        EnsureCooldownFolder();

        if (!m_Store)
            m_Store = new VehicleSalvagingCooldownStore();

        if (!m_Store.Cooldowns)
        {
            m_Store.Cooldowns = new array<ref VehicleSalvagingCooldownEntry>();
        }

        m_Store.Cooldowns.Clear();

        int now = GetCurrentTimeSeconds();

        for (int i = 0; i < m_Cooldowns.Count(); i++)
        {
            string key = m_Cooldowns.GetKey(i);
            int expiresAt = m_Cooldowns.Get(key);

            if (expiresAt <= now)
                continue;

            VehicleSalvagingCooldownEntry entry = new VehicleSalvagingCooldownEntry();
            entry.Key = key;
            entry.ExpiresAt = expiresAt;
            m_Store.Cooldowns.Insert(entry);
        }

        JsonFileLoader<VehicleSalvagingCooldownStore>.JsonSaveFile(GetCooldownFile(), m_Store);
    }

    protected void EnsureCooldownFolder()
    {
        if (!FileExist(GetCooldownFolder()))
            MakeDirectory(GetCooldownFolder());
    }

    protected string GetCooldownFolder()
    {
        return "$profile:VehicleSalvaging";
    }

    protected string GetCooldownFile()
    {
        return "$profile:VehicleSalvaging/VehicleSalvagingCooldowns.json";
    }

    protected string BuildCooldownKey(string partType, ActionTarget target)
    {
        Object wreck = GetTargetWreckObject(target);
        string wreckType = "unknown";
        string positionKey = "unknown";

        if (wreck)
        {
            wreckType = wreck.GetType();
            wreckType.ToLower();

            vector objectPosition = wreck.GetPosition();
            positionKey = objectPosition.ToString();

            if (objectPosition == vector.Zero && target)
                positionKey = target.GetCursorHitPos().ToString();
        }
        else if (target)
        {
            positionKey = target.GetCursorHitPos().ToString();
        }

        return partType + "_" + wreckType + "_" + positionKey;
    }

    protected Object GetTargetWreckObject(ActionTarget target)
    {
        if (!target)
            return null;

        Object targetObject = target.GetObject();

        if (!targetObject)
            targetObject = target.GetParent();

        return targetObject;
    }

    protected int GetCurrentTimeSeconds()
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;

        GetYearMonthDayUTC(year, month, day);
        GetHourMinuteSecondUTC(hour, minute, second);

        int days = 0;

        for (int y = 2020; y < year; y++)
        {
            days += 365;

            if (IsLeapYear(y))
                days += 1;
        }

        days += GetDaysBeforeMonth(month, IsLeapYear(year));
        days += day - 1;

        return (days * 86400) + (hour * 3600) + (minute * 60) + second;
    }

    protected bool IsLeapYear(int year)
    {
        if ((year % 400) == 0)
            return true;

        if ((year % 100) == 0)
            return false;

        return (year % 4) == 0;
    }

    protected int GetDaysBeforeMonth(int month, bool leapYear)
    {
        int leapDay = 0;

        if (leapYear)
            leapDay = 1;

        switch (month)
        {
            case 1:
                return 0;
            case 2:
                return 31;
            case 3:
                return 59 + leapDay;
            case 4:
                return 90 + leapDay;
            case 5:
                return 120 + leapDay;
            case 6:
                return 151 + leapDay;
            case 7:
                return 181 + leapDay;
            case 8:
                return 212 + leapDay;
            case 9:
                return 243 + leapDay;
            case 10:
                return 273 + leapDay;
            case 11:
                return 304 + leapDay;
            case 12:
                return 334 + leapDay;
        }

        return 0;
    }
}
