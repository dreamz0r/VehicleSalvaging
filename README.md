# Vehicle Salvaging

https://steamcommunity.com/sharedfiles/filedetails/?id=3729523717

Vehicle Salvaging is a DayZ mod that lets players salvage useful parts from supported vehicle wrecks by using configured hand tools.

The mod adds custom continuous actions for car wrecks and vanilla heli crash wrecks. When a player targets a supported wreck while holding the configured tool, the matching salvage action appears. If the action completes, the wreck is marked as searched for that specific part type and the player has a configurable chance to receive a damaged part.

Each part search is tracked separately. Searching a wreck for a spark plug does not block searching the same wreck for a radiator, battery, glow plug, or heli part.

## Salvage Actions

Default actions:

| Default tool | Action text | Default item | Wreck categories |
| --- | --- | --- | --- |
| `LugWrench` | `Salvage <item display name>` | `SparkPlug` | Passenger gasoline and police gasoline wrecks |
| `PipeWrench` | `Salvage <item display name>` | `CarRadiator` | Passenger, police, light diesel, light van, and heavy diesel wrecks |
| `Pliers` | `Salvage <item display name>` | `CarBattery` | Passenger, police, light diesel, and light van wrecks |
| `Pliers` | `Salvage <item display name>` | `TruckBattery` | Heavy diesel wrecks |
| `LugWrench` | `Salvage <item display name>` | `GlowPlug` | Light diesel, light van, and heavy diesel wrecks |
| `Pliers` | `Salvage <item display name>` | `ExpansionHelicopterBattery` | Vanilla heli crash wrecks |
| `Wrench` | `Salvage <item display name>` | `ExpansionHydraulicHoses` | Vanilla heli crash wrecks |
| `LugWrench` | `Salvage <item display name>` | `ExpansionIgniterPlug` | Vanilla heli crash wrecks |

The displayed action name and chat messages use the configured output item's in-game display name from `CfgVehicles <ClassName> displayName`. If a server owner changes `HelicopterBatteryItem` to a custom item, the action and messages will use that custom item's display name.

Default heli wreck classnames:

```json
"wreck_uh1y",
"wreck_uh1y_de",
"wreck_mi8",
"wreck_mi8_de",
"wreck_mi8_crashed",
"wreck_mi8_crashed_de"
```

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
      ActionSalvageHelicopterBattery.c
      ActionSalvageHydraulicHoses.c
      ActionSalvageIgniterPlug.c
      ActionSalvageRadiator.c
      ActionSalvageRegistration.c
      ActionSalvageSparkPlug.c
      ActionSalvageTruckBattery.c
      VehicleSalvagingActionBase.c
      VehicleSalvagingConfig.c
      VehicleSalvagingConfigSync.c
      VehicleSalvagingCooldownManager.c
      VehicleSalvagingTools.c
      VehicleSalvagingWreckConfig.c
      VehicleSalvagingWrecks.c
    5_Mission/
      VehicleSalvagingServerInit.c
```

Important files:

- `ActionSalvage*.c` contains the individual salvage actions.
- `ActionSalvageRegistration.c` registers all custom actions with DayZ.
- `VehicleSalvagingActionBase.c` contains shared action behavior, tool damage, already-searched messaging, and dynamic display-name text.
- `VehicleSalvagingConfig.c` loads and validates the main server config.
- `VehicleSalvagingConfigSync.c` sends server config to clients so online action visibility uses server settings.
- `VehicleSalvagingCooldownManager.c` stores per-wreck, per-part cooldowns.
- `VehicleSalvagingTools.c` adds the salvage actions to `PlayerBase`.
- `VehicleSalvagingWreckConfig.c` loads and validates wreck-to-part lists.
- `VehicleSalvagingWrecks.c` checks target wreck classnames against the loaded wreck config.
- `VehicleSalvagingServerInit.c` creates and validates profile JSON files when the server starts and syncs config to connecting clients.
- `WreckSalvageCategories.md` is the readable planning reference for car wreck categories.

## Server JSON Files

On server startup, the mod creates this folder in the server profile:

```text
$profile:VehicleSalvaging
```

In DayZ, `$profile:` resolves to the folder set by the server `-profiles` launch parameter. For example, if the server starts with `-profiles=profiles`, these files will be created inside `profiles/VehicleSalvaging`.

Editable server config:

```text
$profile:VehicleSalvaging/VehicleSalvagingConfig.json
```

Editable wreck-to-part config:

```text
$profile:VehicleSalvaging/VehicleSalvagingWreckConfig.json
```

Runtime cooldown data:

```text
$profile:VehicleSalvaging/VehicleSalvagingCooldowns.json
```

`VehicleSalvagingCooldowns.json` is cleared during every server startup, then reused for cooldowns during that runtime.

Server owners should edit the JSON files in `$profile:VehicleSalvaging`, not the packed script files. The mod also includes `VehicleSalvagingConfig.example.json` and `VehicleSalvagingWreckConfig.example.json` at the mod root as readable examples.

## Main Settings

### Cooldown

```json
"CooldownSeconds": 7200
```

`7200` is 2 hours in seconds.

Cooldowns are part-specific and wreck-specific. Cooldown keys use the part type, wreck classname, and wreck world position. If the wreck object position is unavailable, the scripts fall back to the action target's cursor hit position.

### Find Chance

Each salvage action has its own chance:

```json
"SparkPlugChance": 0.15,
"RadiatorChance": 0.15,
"CarBatteryChance": 0.15,
"TruckBatteryChance": 0.15,
"GlowPlugChance": 0.15,
"HelicopterBatteryChance": 0.15,
"HydraulicHosesChance": 0.15,
"IgniterPlugChance": 0.15
```

`0.15` means a 15% chance to find the part. Use `1.00` to always find the part.

### Salvaged Item Condition

Each found part receives a random DayZ health level between:

```json
"BestPartHealthLevel": 0,
"WorstPartHealthLevel": 4
```

DayZ health levels:

- `0` = pristine
- `1` = worn
- `2` = damaged
- `3` = badly damaged
- `4` = ruined

Invalid values are clamped to `0..4`, and reversed values are swapped when the config is saved.

### Enable Or Disable Actions

Each action can be toggled:

```json
"EnableSparkPlugSalvage": true,
"EnableRadiatorSalvage": true,
"EnableCarBatterySalvage": true,
"EnableTruckBatterySalvage": true,
"EnableGlowPlugSalvage": true,
"EnableHelicopterBatterySalvage": true,
"EnableHydraulicHosesSalvage": true,
"EnableIgniterPlugSalvage": true
```

Set a value to `false` to disable that salvage action.

### Configure Tools

Each salvage action has a configurable required tool classname:

```json
"SparkPlugTool": "LugWrench",
"RadiatorTool": "PipeWrench",
"CarBatteryTool": "Pliers",
"TruckBatteryTool": "Pliers",
"GlowPlugTool": "LugWrench",
"HelicopterBatteryTool": "Pliers",
"HydraulicHosesTool": "Wrench",
"IgniterPlugTool": "LugWrench"
```

The player must hold the configured, non-ruined tool for the action to appear and run. Tool checks use `IsKindOf`, so child classes of a configured tool also work.

### Configure Salvaged Items

Each salvage action has a configurable output item classname:

```json
"SparkPlugItem": "SparkPlug",
"RadiatorItem": "CarRadiator",
"CarBatteryItem": "CarBattery",
"TruckBatteryItem": "TruckBattery",
"GlowPlugItem": "GlowPlug",
"HelicopterBatteryItem": "ExpansionHelicopterBattery",
"HydraulicHosesItem": "ExpansionHydraulicHoses",
"IgniterPlugItem": "ExpansionIgniterPlug"
```

This lets servers replace Expansion heli parts with custom or vanilla items. The action label and chat messages use the configured item's in-game display name.

### Tool Durability

Every completed salvage action removes 10% of the tool's maximum durability. Tools are not deleted by salvage damage; they degrade through normal quality states and stop at ruined.

## Changing Which Wrecks A Script Uses

Server owners can change which wrecks award which parts in:

```text
$profile:VehicleSalvaging/VehicleSalvagingWreckConfig.json
```

The file has one array for each salvageable part:

```json
{
    "SparkPlugWrecks": ["land_wreck_hb01_aban1_blue"],
    "RadiatorWrecks": ["land_wreck_hb01_aban1_blue"],
    "CarBatteryWrecks": ["land_wreck_hb01_aban1_blue"],
    "TruckBatteryWrecks": ["land_wreck_truck01_aban1_blue"],
    "GlowPlugWrecks": ["land_wreck_offroad02_aban1"],
    "HelicopterBatteryWrecks": ["wreck_uh1y"],
    "HydraulicHosesWrecks": ["wreck_uh1y"],
    "IgniterPlugWrecks": ["wreck_uh1y"]
}
```

Add a wreck classname to a part array to allow that wreck to award that item. Remove a wreck classname from a part array to prevent that item from being found there.

Classnames are normalized to lowercase when the file loads. Empty entries are removed when the file is saved.

The scripts use these wreck helpers:

```c
VehicleSalvagingWrecks.IsSparkPlugWreck(objType)
VehicleSalvagingWrecks.IsRadiatorWreck(objType)
VehicleSalvagingWrecks.IsCarBatteryWreck(objType)
VehicleSalvagingWrecks.IsTruckBatteryWreck(objType)
VehicleSalvagingWrecks.IsGlowPlugWreck(objType)
VehicleSalvagingWrecks.IsHelicopterBatteryWreck(objType)
VehicleSalvagingWrecks.IsHydraulicHosesWreck(objType)
VehicleSalvagingWrecks.IsIgniterPlugWreck(objType)
```

## Online Server Config Sync

Action visibility is checked client-side, but the editable config lives on the server. To avoid clients using stale local/default config, the server syncs both config files to each connecting client.

This means online clients should see action availability based on the dedicated server's configured tools, enabled actions, yielded items, and wreck lists.

## Testing Tips

For quick testing, temporarily set the relevant find chance to `1.00`:

```json
"SparkPlugChance": 1.00
```

If an action does not appear:

- Confirm the action is enabled in `VehicleSalvagingConfig.json`.
- Confirm the action is registered in `ActionSalvageRegistration.c`.
- Confirm the player is holding the configured non-ruined tool.
- Confirm the target wreck classname exists in that part's wreck array.
- Confirm the server profile JSON has been edited, not the packed example file.
- Restart/rejoin after config edits so clients receive the latest synced config.

If the action appears but no item is created:

- Remember the default find chance is 15%.
- Temporarily set the chance to `1.00` to verify item creation.
- Confirm the configured output item classname exists on the server and client.

If the wreck has already been searched for that part, the animation is blocked before it begins and the player receives an already-searched message.

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
