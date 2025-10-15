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
    "SPECIAL_ABILITY_ONE","SPECIAL_ABILITY_ONE_DESC","SPECIAL_ABILITY_TWO","SPECIAL_ABILITY_TWO_DESC",
    "SPECIAL_ABILITY_THREE","SPECIAL_ABILITY_THREE_DESC","SPECIAL_ABILITY_FOUR","SPECIAL_ABILITY_FOUR_DESC",
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
    return data.get(key, default) if isinstance(data, dict) else default

def extract_first_n(entries, n):
    """Extract up to n (name, desc) pairs from a list of dictionaries."""
    pairs = []
    for i in range(n):
        if isinstance(entries, list) and i < len(entries):
            name = entries[i].get("name", 0)
            desc = entries[i].get("desc", 0)
        else:
            name, desc = 0, 0
        pairs.append((name, desc))
    return pairs

def extract_speed(speed_dict):
    out = {"type": 0, "walk": 0, "fly": 0, "swim": 0, "climb": 0, "burrow": 0}
    if not isinstance(speed_dict, dict):
        return out
    if speed_dict:
        out["type"] = ",".join(sorted(speed_dict.keys()))
    def parse_speed(val):
        if val is None:
            return 0
        if isinstance(val, int):
            return val
        if isinstance(val, str):
            digits = ''.join(ch for ch in val if ch.isdigit())
            return int(digits) if digits else 0
        return 0
    out["walk"] = parse_speed(speed_dict.get("walk", 0))
    out["fly"] = parse_speed(speed_dict.get("fly", 0))
    out["swim"] = parse_speed(speed_dict.get("swim", 0))
    out["climb"] = parse_speed(speed_dict.get("climb", 0))
    out["burrow"] = parse_speed(speed_dict.get("burrow", 0))
    return out

def extract_range(senses, key):
    val = get_value(senses, key, 0)
    if isinstance(val, int):
        return val
    if isinstance(val, str):
        digits = ''.join(ch for ch in val if ch.isdigit())
        return int(digits) if digits else 0
    return 0

def parse_saving_throws(mon):
    throws = {"STR":0,"DEX":0,"CON":0,"INT":0,"WIS":0,"CHA":0}
    saving_throws = mon.get("saving_throws") or mon.get("saves")
    if isinstance(saving_throws, dict) and saving_throws:
        mapping = {
            "str": "STR", "strength": "STR",
            "dex": "DEX", "dexterity": "DEX",
            "con": "CON", "constitution": "CON",
            "int": "INT", "intelligence": "INT",
            "wis": "WIS", "wisdom": "WIS",
            "cha": "CHA", "charisma": "CHA"
        }
        for k, v in saving_throws.items():
            key_lower = k.lower()
            if key_lower in mapping:
                sval = ''.join(ch for ch in str(v) if ch in "-0123456789")
                throws[mapping[key_lower]] = int(sval) if sval else 0
        return throws
    profs = mon.get("proficiencies", [])
    if isinstance(profs, list):
        for p in profs:
            val = p.get("value", None)
            prof = p.get("proficiency", {})
            pname = prof.get("name", "") or prof.get("index", "")
            if isinstance(pname, str):
                name_lower = pname.lower()
                if "saving throw" in name_lower:
                    for ab in ["str","dex","con","int","wis","cha"]:
                        if ab in name_lower:
                            throws[ab.upper()] = int(val) if val is not None else 0
    return throws

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
            ac_item = mon["armor_class"][0]
            row["ARMOR_CLASS"] = ac_item.get("value") or ac_item.get("ac") or 0
        elif isinstance(mon.get("armor_class"), dict):
            row["ARMOR_CLASS"] = mon["armor_class"].get("ac", 0)
        else:
            row["ARMOR_CLASS"] = mon.get("armor_class", 0)

        # Hit points
        if isinstance(mon.get("hit_points"), int):
            row["HITPOINTS_AVG"] = mon["hit_points"]
        elif isinstance(mon.get("hit_points"), dict):
            row["HITPOINTS_AVG"] = mon["hit_points"].get("average", mon["hit_points"].get("value", 0))
        else:
            row["HITPOINTS_AVG"] = mon.get("hit_points", 0)
        row["HIT_DICE"] = mon.get("hit_dice", 0)
        row["HITPOINTS_ROLL"] = mon.get("hit_points_roll", 0)

        # Speed
        speeds = extract_speed(mon.get("speed", {}))
        for k, v in speeds.items():
            row[f"SPEED_{k.upper()}"] = v

        # Ability scores
        stats_list = mon.get("stats", [])
        for key, idx in zip(["STR","DEX","CON","INT","WIS","CHA"], range(6)):
            row[key] = int(mon.get(key.lower(), stats_list[idx] if len(stats_list) > idx else 0) or 0)

        # Prof bonus
        row["PROF_BONUS"] = mon.get("proficiency_bonus", mon.get("proficiency", 0)) or 0

        # Saving throws
        throws = parse_saving_throws(mon)
        for ab in ["STR","DEX","CON","INT","WIS","CHA"]:
            row[f"THROW_{ab}"] = throws.get(ab, 0)

        # Skills
        skills_obj = mon.get("skills", {})
        if isinstance(skills_obj, dict) and skills_obj:
            row["SKILLS"] = ", ".join(f"{k.upper()} +{v}" for k, v in skills_obj.items())
        else:
            row["SKILLS"] = 0

        # Languages
        langs = mon.get("languages", 0)
        row["LANGUAGES"] = ", ".join(langs) if isinstance(langs, list) else langs or 0

        # Senses
        senses = mon.get("senses", {})
        if isinstance(senses, dict) and senses:
            row["SENSES"] = ", ".join(f"{k} {v}" for k,v in senses.items())
            for sense in ["darkvision","tremorsense","blindsight","truesight"]:
                row[f"RANGE_{sense.upper()}"] = extract_range(senses, sense)

        # Environment
        env = mon.get("environments", mon.get("environment", mon.get("environment_list", [])))
        row["ENVIRONMENT"] = ", ".join(env) if isinstance(env, list) else env or 0

        # === SPECIAL ABILITIES ===
        special_abilities = extract_first_n(mon.get("special_abilities", []), 4)
        for idx, (name, desc) in enumerate(special_abilities, start=1):
            row[f"SPECIAL_ABILITY_{['ONE','TWO','THREE','FOUR'][idx-1]}"] = name
            row[f"SPECIAL_ABILITY_{['ONE','TWO','THREE','FOUR'][idx-1]}_DESC"] = desc

        # === ATTACKS / ACTIONS ===
        attacks = extract_first_n(mon.get("actions", []), 5)
        for idx, (name, desc) in enumerate(attacks, start=1):
            if idx == 5:
                row["ATTACK_5_TYPE"] = name
                row["ATTACK_5_DESC"] = desc
            else:
                row[f"ATTACK_{idx}"] = name
                row[f"ATTACK_{idx}_DESC"] = desc

        writer.writerow(row)

print(f"✅ Conversion complete! Wrote {len(monsters)} entries to {OUTPUT_CSV}")