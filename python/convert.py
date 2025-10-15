import json
import csv

# === CONFIG ===
INPUT_JSON = "monsters.json" # Path to your input JSON file
OUTPUT_CSV = "monsters.csv" # Output CSV file name

# === CSV HEADER ===
headers = [
    "ID","NAME","CR","TYPE","SIZE","ARMOR_CLASS","HITPOINTS_AVG","HIT_DICE","HITPOINTS_ROLL",
    "SPEED_TYPE","SPEED_WALK","SPEED_FLY","SPEED_SWIM","SPEED_CLIMB","SPEED_BURROW",
    "ALIGNMENT","LEGENDARY","STR","DEX","CON","INT","WIS","CHA","PROF_BONUS",
    "THROW_STR","THROW_DEX","THROW_CON","THROW_INT","THROW_WIS","THROW_CHA",
    "SKILLS","LANGUAGES","SENSES","RANGE_DARKVISION","RANGE_TREMORSENSE","RANGE_BLINDSIGHT","RANGE_TRUESIGHT",
    "ABILITY_ONE","ABILITY_ONE_DESC","ABILITY_TWO","ABILITY_TWO_DESC","ABILITY_THREE","ABILITY_THREE_DESC","ABILITY_FOUR","ABILITY_FOUR_DESC",
    "ATTACK_1","ATTACK_1_DESC","ATTACK_2","ATTACK_2_DESC","ATTACK_3","ATTACK_3_DESC","ATTACK_4","ATTACK_4_DESC","ATTACK_5_TYPE","ATTACK_5_DESC",
    "ACTION_LEG","ACTION_LEG1","ACTION_LEG1_DESC","ACTION_LEG2","ACTION_LEG2_DESC","ACTION_LEG3","ACTION_LEG3_DESC",
    "ACTION_LAIR","ACTION_LAIR1","ACTION_LAIR1_DESC","ACTION_LAIR2","ACTION_LAIR2_DESC","ACTION_LAIR3","ACTION_LAIR3_DESC",
    "REGIONALEFFECT","REGIONALEFFECT1","REGIONALEFFECT2","REGIONALEFFECT3","ENDREGIONALEFFECT",
    "ENVIRONMENT","BA1","BA1_DESC","BA2","BA2_DESC","BA3","BA3_DESC","BA4","BA4_DESC",
    "REACTION1","REACTION1_DESC","REACTION2","REACTION2_DESC","REACTION3","REACTION3_DESC",
    "VILL_ACTION","VILL_ACTION1","VILL_ACTION1_DESC","VILL_ACTION2","VILL_ACTION2_DESC","VILL_ACTION3","VILL_ACTION3_DESC",
    "UTILITY_SPELLS","UTILITY_SPELLS_LIST",
    "FEATURE1","FEATURE1_DESC","FEATURE2","FEATURE2_DESC","FEATURE3","FEATURE3_DESC","FEATURE4","FEATURE4_DESC","FEATURE5","FEATURE5_DESC"
]

# === HELPER FUNCTIONS ===

def get_value(data, key, default=0):
    """Safely get a key from a dict with fallback."""
    return data.get(key, default) if isinstance(data, dict) else default

def extract_first_n(entries, n):
    """Extract up to n (name, desc) pairs from a list of dictionaries."""
    pairs = []
    for i in range(n):
        if i < len(entries):
            name = entries[i].get("name", 0)
            desc = entries[i].get("desc", 0)
        else:
            name, desc = 0, 0
        pairs.append((name, desc))
    return pairs

def extract_speed(speed_dict):
    """Normalize speeds to 0 if missing."""
    return {
        "type": ", ".join(speed_dict.keys()) if speed_dict else 0,
        "walk": get_value(speed_dict, "walk", 0),
        "fly": get_value(speed_dict, "fly", 0),
        "swim": get_value(speed_dict, "swim", 0),
        "climb": get_value(speed_dict, "climb", 0),
        "burrow": get_value(speed_dict, "burrow", 0)
    }

def extract_range(senses, key):
    """Extract range from sense description."""
    val = get_value(senses, key, 0)
    if isinstance(val, int):
        return val
    if isinstance(val, str) and any(ch.isdigit() for ch in val):
        return int(''.join(ch for ch in val if ch.isdigit()))
    return 0

# === MAIN CONVERSION ===

with open(INPUT_JSON, "r", encoding="utf-8") as f:
    monsters = json.load(f)

with open(OUTPUT_CSV, "w", newline='', encoding="utf-8") as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=headers)
    writer.writeheader()

    for i, mon in enumerate(monsters, start=1):
        row = {h: 0 for h in headers}
        row["ID"] = i
        row["NAME"] = mon.get("name", 0)
        row["CR"] = str(mon.get("challenge_rating", "0")) # always string
        row["TYPE"] = mon.get("type", 0)
        row["SIZE"] = mon.get("size", 0)
        row["ALIGNMENT"] = mon.get("alignment", 0)

        # Armor class
        if isinstance(mon.get("armor_class"), list) and mon["armor_class"]:
            row["ARMOR_CLASS"] = mon["armor_class"][0].get("ac", 0)
        elif isinstance(mon.get("armor_class"), dict):
            row["ARMOR_CLASS"] = mon["armor_class"].get("ac", 0)
        else:
            row["ARMOR_CLASS"] = mon.get("armor_class", 0)

        # Hit points
        hp = mon.get("hit_points", {})
        if isinstance(hp, dict):
            row["HITPOINTS_AVG"] = get_value(hp, "average", 0)
            row["HIT_DICE"] = get_value(hp, "formula", 0)
            row["HITPOINTS_ROLL"] = get_value(hp, "formula", 0)
        else:
            row["HITPOINTS_AVG"] = mon.get("hit_points", 0)

        # Speed
        speeds = extract_speed(mon.get("speed", {}))
        row["SPEED_TYPE"] = speeds["type"]
        row["SPEED_WALK"] = speeds["walk"]
        row["SPEED_FLY"] = speeds["fly"]
        row["SPEED_SWIM"] = speeds["swim"]
        row["SPEED_CLIMB"] = speeds["climb"]
        row["SPEED_BURROW"] = speeds["burrow"]

        # Abilities
        stats = mon.get("stats", [0, 0, 0, 0, 0, 0])
        for k, ability in zip(["STR", "DEX", "CON", "INT", "WIS", "CHA"], stats):
            row[k] = ability

        # Traits
        traits = extract_first_n(mon.get("traits", []), 4)
        for idx, (name, desc) in enumerate(traits, start=1):
            row[f"ABILITY_{['ONE','TWO','THREE','FOUR'][idx-1]}"] = name
            row[f"ABILITY_{['ONE','TWO','THREE','FOUR'][idx-1]}_DESC"] = desc

        # Actions
        actions = extract_first_n(mon.get("actions", []), 5)
        for idx, (name, desc) in enumerate(actions, start=1):
            if idx < 5:
                row[f"ATTACK_{idx}"] = name
                row[f"ATTACK_{idx}_DESC"] = desc
            else:
                row["ATTACK_5_TYPE"] = name
                row["ATTACK_5_DESC"] = desc

        # Legendary Actions
        legs = extract_first_n(mon.get("legendary_actions", []), 3)
        if legs and any(a[0] != 0 for a in legs):
            row["LEGENDARY"] = "Legendary"
        for idx, (name, desc) in enumerate(legs, start=1):
            row[f"ACTION_LEG{idx}"] = name
            row[f"ACTION_LEG{idx}_DESC"] = desc

        # Lair Actions
        lairs = extract_first_n(mon.get("lair_actions", []), 3)
        for idx, (name, desc) in enumerate(lairs, start=1):
            row[f"ACTION_LAIR{idx}"] = name
            row[f"ACTION_LAIR{idx}_DESC"] = desc

        # Regional Effects
        regs = mon.get("regional_effects", [])
        for j in range(3):
            row[f"REGIONALEFFECT{j+1}"] = regs[j] if j < len(regs) else 0

        # Skills, Languages, Senses
        row["SKILLS"] = ", ".join(f"{k.upper()} {v}" for k, v in mon.get("skills", {}).items()) or 0
        row["LANGUAGES"] = ", ".join(mon.get("languages", [])) or 0
        senses = mon.get("senses", {})
        row["SENSES"] = ", ".join(f"{k} {v}" for k, v in senses.items()) or 0
        row["RANGE_DARKVISION"] = extract_range(senses, "darkvision")
        row["RANGE_TREMORSENSE"] = extract_range(senses, "tremorsense")
        row["RANGE_BLINDSIGHT"] = extract_range(senses, "blindsight")
        row["RANGE_TRUESIGHT"] = extract_range(senses, "truesight")

        # Environment
        row["ENVIRONMENT"] = ", ".join(mon.get("environments", [])) or 0

        writer.writerow(row)

print(f"✅ Conversion complete! Wrote {len(monsters)} entries to {OUTPUT_CSV}")