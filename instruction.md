```bash
#Emscripten:
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
```

build for emscripten
```bash
emcmake cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -s USE_FREETYPE=1 -s USE_HARFBUZZ=1

```


``` bash
#To view html from build/release/:
python3 -m http.server 8080
```

linked list for build encounter
search field on creature and player side


CREATE TABLE monsters (
    id INTEGER PRIMARY KEY,
    name TEXT,
    cr TEXT,
    type TEXT,
    size TEXT,
    armor_class INTEGER,
    hitpoints_avg INTEGER,
    hit_dice TEXT,
    hitpoints_roll TEXT,
    speed_type TEXT,
    speed_walk INTEGER,
    speed_fly INTEGER,
    speed_swim INTEGER,
    speed_climb INTEGER,
    speed_burrow INTEGER,
    alignment TEXT,
    legendary TEXT,
    str INTEGER,
    dex INTEGER,
    con INTEGER,
    int INTEGER,
    wis INTEGER,
    cha INTEGER,
    prof_bonus INTEGER,
    throw_str INTEGER,
    throw_dex INTEGER,
    throw_con INTEGER,
    throw_int INTEGER,
    throw_wis INTEGER,
    throw_cha INTEGER,
    skills TEXT,
    languages TEXT,
    senses TEXT,
    range_darkvision INTEGER,
    range_tremorsense INTEGER,
    range_blindsight INTEGER,
    range_truesight INTEGER,
    special_ability_one TEXT,
    special_ability_one_desc TEXT,
    special_ability_two TEXT,
    special_ability_two_desc TEXT,
    special_ability_three TEXT,
    special_ability_three_desc TEXT,
    special_ability_four TEXT,
    special_ability_four_desc TEXT,
    attack_1 TEXT,
    attack_1_desc TEXT,
    attack_2 TEXT,
    attack_2_desc TEXT,
    attack_3 TEXT,
    attack_3_desc TEXT,
    attack_4 TEXT,
    attack_4_desc TEXT,
    attack_5_type TEXT,
    attack_5_desc TEXT,
    action_leg TEXT,
    action_leg1 TEXT,
    action_leg1_desc TEXT,
    action_leg2 TEXT,
    action_leg2_desc TEXT,
    action_leg3 TEXT,
    action_leg3_desc TEXT,
    action_lair TEXT,
    action_lair1 TEXT,
    action_lair1_desc TEXT,
    action_lair2 TEXT,
    action_lair2_desc TEXT,
    action_lair3 TEXT,
    action_lair3_desc TEXT,
    regionaleffect TEXT,
    regionaleffect1 TEXT,
    regionaleffect2 TEXT,
    regionaleffect3 TEXT,
    endregionaleffect TEXT,
    environment TEXT,
    ba1 TEXT,
    ba1_desc TEXT,
    ba2 TEXT,
    ba2_desc TEXT,
    ba3 TEXT,
    ba3_desc TEXT,
    ba4 TEXT,
    ba4_desc TEXT,
    reaction1 TEXT,
    reaction1_desc TEXT,
    reaction2 TEXT,
    reaction2_desc TEXT,
    reaction3 TEXT,
    reaction3_desc TEXT,
    vill_action TEXT,
    vill_action1 TEXT,
    vill_action1_desc TEXT,
    vill_action2 TEXT,
    vill_action2_desc TEXT,
    vill_action3 TEXT,
    vill_action3_desc TEXT,
    utility_spells TEXT,
    utility_spells_list TEXT,
    feature1 TEXT,
    feature1_desc TEXT,
    feature2 TEXT,
    feature2_desc TEXT,
    feature3 TEXT,
    feature3_desc TEXT,
    feature4 TEXT,
    feature4_desc TEXT,
    feature5 TEXT,
    feature5_desc TEXT
);