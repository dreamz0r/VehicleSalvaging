# Vehicle Salvaging

https://steamcommunity.com/sharedfiles/filedetails/?id=3729523717

Vehicle Salvaging is a DayZ mod that lets players salvage useful vehicle parts from vanilla vehicle wrecks by using appropriate hand tools.

The mod adds custom continuous actions to tools such as pliers, pipe wrenches, and lug wrenches. When a player targets a supported wreck, the matching salvage action appears. If the action completes, the wreck is marked as searched for that specific part type and the player has a chance to receive a damaged vehicle part.

## Current Salvage Actions

| Tool | Action | Salvaged item | Wreck categories |
| --- | --- | --- | --- |
| `PipeWrench` | `Salvage radiator` | `CarRadiator` | Passenger, police, light military diesel, light van, and heavy diesel wrecks |
| `Pliers` | `Salvage car battery` | `CarBattery` | Passenger, police, light military diesel, and light van wrecks |
| `Pliers` | `Salvage truck battery` | `TruckBattery` | Heavy diesel wrecks |
| `LugWrench` | `Salvage spark plug` | `SparkPlug` | Passenger gasoline and police gasoline wrecks |
| `LugWrench` | `Salvage glow plug` | `GlowPlug` | Light military diesel, light van, and heavy diesel wrecks |

Trailers, caravans, and aircraft are intentionally not used by the current salvage scripts.

## File Layout

```text
VehicleSalvaging/
  config.cpp
  README.md
  VehicleSalvagingConfig.example.json
  VehicleSalvagingWreckConfig.example.json
  WreckSalvageCategories.md
  scripts/
    4_World/
      ActionSalvageBattery.c
      ActionSalvageGlowPlug.c
      ActionSalvageRadiator.c
      ActionSalvageRegistration.c
      ActionSalvageSparkPlug.c
      ActionSalvageTruckBattery.c
      VehicleSalvagingConfig.c
      VehicleSalvagingCooldownManager.c
      VehicleSalvagingTools.c
      VehicleSalvagingWreckConfig.c
      VehicleSalvagingWrecks.c
    5_Mission/
      VehicleSalvagingServerInit.c
```

Important files:

- `VehicleSalvagingTools.c` controls which tools get which salvage actions.
- `ActionSalvageRegistration.c` registers all custom actions with DayZ.
- Each `ActionSalvage*.c` file contains one salvage action.
- `VehicleSalvagingConfig.c` loads server-owner settings from JSON.
- `VehicleSalvagingCooldownManager.c` saves and loads persistent per-wreck cooldowns.
- `VehicleSalvagingWreckConfig.c` loads server-owner wreck-to-part lists from JSON.
- `VehicleSalvagingWrecks.c` checks target wreck classnames against the loaded wreck config.
- `VehicleSalvagingServerInit.c` creates and validates profile JSON files when the server starts.
- `WreckSalvageCategories.md` is the readable planning reference for which wrecks should belong to which salvage category.
- `config.cpp` controls the mod identity and script load path.

## Server JSON Files

On server startup, the mod creates this folder in the server profile:

```text
$profile:VehicleSalvaging
```

In DayZ, `$profile:` resolves to the folder set by the server `-profiles` launch parameter. For example, if the server starts with `-profiles=profiles`, these files will be created inside `profiles/VehicleSalvaging`.

The editable server config is:

```text
$profile:VehicleSalvaging/VehicleSalvagingConfig.json
```

The editable wreck-to-part config is:

```text
$profile:VehicleSalvaging/VehicleSalvagingWreckConfig.json
```

The cooldown data file is:

```text
$profile:VehicleSalvaging/VehicleSalvagingCooldowns.json
```

`VehicleSalvagingCooldowns.json` is cleared during every server startup, then reused for cooldowns during that runtime.

Server owners should edit the JSON files in `$profile:VehicleSalvaging`, not the packed script files. The mod creates these files during `MissionServer.OnInit`, so they should exist after the server has started even if no player has used a salvage action yet. The mod also includes `VehicleSalvagingConfig.example.json` and `VehicleSalvagingWreckConfig.example.json` at the mod root as readable examples.

## Important Settings

The JSON config has the main tuning points server owners are expected to change.

### Cooldown

Search for:

```c
"CooldownSeconds": 7200
```

`7200` is 2 hours in seconds.

Example values:

- `3600` = 1 hour
- `1800` = 30 minutes

Cooldowns are part-specific and wreck-specific. Searching one wreck for a spark plug does not block another wreck of the same model, and it does not block searching the same wreck for a radiator, battery, truck battery, or glow plug.

Cooldown keys use the part type, wreck classname, and wreck world position. If the wreck object position is unavailable, the scripts fall back to the action target's cursor hit position.

```c
return partType + "_" + wreckType + "_" + positionKey;
```

Cooldowns are saved to JSON with an absolute UTC expiry time during a server runtime, but the file is cleared when the server starts.

### Find Chance

Search for:

```json
"SparkPlugChance": 0.15
```

`0.15` means a 15% chance to find the part.

Example values:

- `0.25` = 25%
- `0.50` = 50%
- `1.00` = always find the part

### Tool Durability

Every completed salvage action removes 10% of the tool's maximum durability. Tools are not deleted by salvage damage; they degrade through the normal quality states and stop at ruined.

### Salvaged Item Condition

Each found part receives a random DayZ health level between:

```json
"BestPartHealthLevel": 0,
"WorstPartHealthLevel": 4
```

DayZ health levels are:

- `0` = pristine
- `1` = worn
- `2` = damaged
- `3` = badly damaged
- `4` = ruined

The default `0` to `4` gives equal odds for every condition. To only spawn rough salvage, use:

```json
"BestPartHealthLevel": 2,
"WorstPartHealthLevel": 4
```

That allows damaged, badly damaged, or ruined parts. Invalid values are clamped to `0..4`, and if the values are reversed the mod swaps them when saving the config.

### Enable Or Disable Actions

Each action can be toggled in JSON:

```json
"EnableSparkPlugSalvage": true,
"EnableRadiatorSalvage": true,
"EnableCarBatterySalvage": true,
"EnableTruckBatterySalvage": true,
"EnableGlowPlugSalvage": true
```

Set a value to `false` to disable that salvage action.

## Changing Which Wrecks A Script Uses

Server owners can change which wrecks award which parts in:

```text
$profile:VehicleSalvaging/VehicleSalvagingWreckConfig.json
```

The file has one array for each salvageable part:

```json
{
    "SparkPlugWrecks": [
        "land_wreck_hb01_aban1_blue"
    ],
    "RadiatorWrecks": [
        "land_wreck_hb01_aban1_blue"
    ],
    "CarBatteryWrecks": [
        "land_wreck_hb01_aban1_blue"
    ],
    "TruckBatteryWrecks": [
        "land_wreck_truck01_aban1_blue"
    ],
    "GlowPlugWrecks": [
        "land_wreck_offroad02_aban1"
    ]
}
```

Add a wreck classname to a part array to allow that wreck to award that item. Remove a wreck classname from a part array to prevent that item from being found there. The tool requirements do not change: spark plugs and glow plugs still use `LugWrench`, radiators still use `PipeWrench`, and batteries still use `Pliers`.

Classnames are normalized to lowercase when the file loads. Empty entries are removed when the file is saved.

The scripts use the shared wreck category helper:

```c
VehicleSalvagingWrecks.IsSparkPlugWreck(objType)
VehicleSalvagingWrecks.IsCarBatteryWreck(objType)
VehicleSalvagingWrecks.IsRadiatorWreck(objType)
VehicleSalvagingWrecks.IsGlowPlugWreck(objType)
VehicleSalvagingWrecks.IsTruckBatteryWreck(objType)
```

Use `WreckSalvageCategories.md` as the source list when moving wrecks between arrays.

Example:

```json
"SparkPlugWrecks": [
    "land_wreck_sed01_aban1_black",
    "land_wreck_sed01_aban1_black_de"
]
```

## Adding A New Salvage Script

To add another salvageable part, follow this pattern.

1. Copy an existing action script, such as `ActionSalvageSparkPlug.c`.
2. Rename the callback class.
3. Rename the action class.
4. Change `m_Text` to the new action name.
5. Change the required held tool check.
6. Change the spawned item classname.
7. Change the cooldown key prefix.
8. Add the new part's wreck array to `VehicleSalvagingWreckConfig.c`.
9. Add a matching helper in `VehicleSalvagingWrecks.c`.
10. Register the action in `ActionSalvageRegistration.c`.
11. Attach the action to a tool in `VehicleSalvagingTools.c`.

For example, if adding an alternator salvage action:

```c
actions.Insert(ActionSalvageAlternator);
```

And in `VehicleSalvagingTools.c`:

```c
modded class Wrench
{
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionSalvageAlternator);
    }
}
```

Use a unique cooldown prefix for every part type when calling the cooldown manager:

```c
VehicleSalvagingCooldownManager.GetInstance().IsOnCooldown("alternator", target);
VehicleSalvagingCooldownManager.GetInstance().MarkSalvaged("alternator", target);
```

This prevents one part search from blocking another part search on the same wreck.

## Testing Tips

For quick testing, temporarily set the find chance to `1.00` in `VehicleSalvagingConfig.json`:

```json
"SparkPlugChance": 1.00
```

After confirming the action works, change it back to the intended value.

If an action does not appear:

- Confirm the action is registered in `ActionSalvageRegistration.c`.
- Confirm the tool has `AddAction(...)` in `VehicleSalvagingTools.c`.
- Confirm the target wreck classname exists in that action script's wreck helper.
- Confirm the player is holding the correct non-ruined tool.
- If the wreck is already on cooldown for that part type, the action is blocked before the animation starts and the player receives an already-searched message.

If the action appears but no item is created:

- Remember the default find chance is 15%.
- Temporarily set the chance to `1.00` to verify item creation.
- Confirm the item classname is correct.

## Current Mod Metadata

The mod is configured in `config.cpp` as:

```c
class VehicleSalvaging
{
    dir = "VehicleSalvaging";
    name = "Vehicle Salvaging";
    author = "Griffin";
    dependencies[] = {"World","Mission"};
}
```

The world scripts load from:

```c
files[] = {"VehicleSalvaging/scripts/4_World"};
```
