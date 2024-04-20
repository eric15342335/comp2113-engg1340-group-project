/**
 * @file names.cpp
 * @brief This file contains the implementation of the stock name generation function.
 * @authors MaxChungsh, eric15342335, comet13579
 */
#include "names.h"
#include <random>
#include <algorithm>
using namespace std;

/** List of stock categories */
string const CategoryList[sizeofCategoryList] = {
    "Adv&Market", "Aero&Def",  "Airlines",       "RenewEnergy", "Auto",        "Banks",
    "Biotech",    "Broadcast", "Casinos&Gaming", "E-Commerce",  "FinServices", "Food&Beverage",
    "Healthcare", "Tech",      "RealEstate",     "Retail",      "Telecom"};

/**
 * Generates a set of unique stock names based on the specified category and quantity.
 * @param category The category index `[0 to sizeofCategoryList-1]` indicating the stock category.
 * @param num The number of stock names to generate.
 * @return A vector of unique stock names.
 * @note Possibility of infinite loop if called `generate_names(0,99999999999999)`.
 */
vector<string> generateName(unsigned int category, unsigned int num) {
    // List of suffixes for stock names
    vector<string> const suffixes = {"Holdings", "Ltd", "Group", "Corp", "Inc", "Enterprises", "Solutions", "Services"};
    vector<string> companyNames;
    random_device rd;
    mt19937 gen(rd());

    switch (category) {
    case 0: { // Generate a name for Adv&Market category
        vector<string> words = {"Alpha",     "Beta",       "Gamma",          "Delta",      "Epsilon",    "Innovate",
                                "Solutions", "Strategies", "Impact",         "Growth",     "Creative",   "Digital",
                                "Marketing", "Brand",      "Communications", "Buzz",       "Genius",     "Company",
                                "Tech",      "Global",     "Dynamic",        "Infinite",   "Revolution", "Evolution",
                                "Power",     "Innovation", "Inspire",        "Transform",  "Future",     "Vision",
                                "Progress",  "Solutions",  "Excellence",     "Advantage",  "Success",    "Fortune",
                                "Ventures",  "Endeavor",   "Pioneers",       "Prosperity", "Synergy",    "Advertising",
                                "Media",     "Promotion",  "Campaign",       "Creative",   "Strategy",   "Market",
                                "Audience",  "Brand",      "Digital",        "Social",     "Influencer"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 1: { // Generate a name for Aero&Def category
        vector<string> words = {
            "Zeus",         "Thor",       "Hulk",       "Loki",     "Ironman",      "Captain",    "America",
            "Valkyrie",     "Odin",       "Hawkeye",    "Levi",     "Black Widow",  "Vegeta",     "Buu",
            "Sasuke",       "Hephaestus", "Ares",       "Poseidon", "Apollo",       "Hera",       "Athena",
            "Artemis",      "Hades",      "Hercules",   "Mjolnir",  "Stormbreaker", "Goku",       "Shield",
            "Infinity",     "Aizen",      "Panther",    "Anya",     "Yor",          "Goalkeeper", "Itachi",
            "Web",          "Ant",        "Man",        "Groot",    "Zhongli",      "Lord",       "Naruto",
            "Gojo",         "Ichigo",     "Kakashi",    "Saitama",  "Witch",        "Air",        "Wings",
            "Flight",       "Rocket",     "Defender",   "Zeon",     "Defense",      "Airborne",   "Aerospace",
            "Missile",      "Anaheim",    "Supersonic", "Bomber",   "Interceptor",  "Pilot",      "Sukuna",
            "Stealth",      "Warrior",    "Aircraft",   "Airman",   "Seiya",        "Sanji",      "Airbase",
            "Stratosphere", "Airshow",    "Combat",     "Zoro"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 2: { // Generate a name for Airlines category
        vector<string> words = {
            "Sky",        "Wings",     "Fly",     "Jet",      "Air",      "Cloud",     "Aviation",  "Aero",
            "Flight",     "High",      "Travel",  "Skyward",  "Lift",     "Airborne",  "Airline",   "Birds",
            "Wingman",    "Up",        "Glide",   "Airbus",   "Propel",   "Cmefly",    "Airfield",  "Skyline",
            "Airspeed",   "Aircrew",   "Airshow", "Airspace", "Airway",   "Aviator",   "Airworthy", "Airstrip",
            "Airman",     "Airfare",   "Airbag",  "Airbus",   "Airtime",  "Takeoff",   "Landing",   "Pilot",
            "Cabin",      "Cockpit",   "Airlift", "Airflow",  "Airliner", "Jetsetter", "Airship",   "Airterminal",
            "Airsteward", "Airstrike", "Airtaxi", "Airway"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 3: { // Generate a name for RenewEnergy&storage category
        vector<string> words = {"Solar",
                                "Wind",
                                "Eco",
                                "Green",
                                "Renew",
                                "Sunny",
                                "Breezy",
                                "Clean",
                                "Efficient",
                                "Power",
                                "Sustainable",
                                "Energize",
                                "Hydro",
                                "Turbine",
                                "Electric",
                                "Sunshine",
                                "Gust",
                                "Nature",
                                "Windy",
                                "Responsible",
                                "Bio",
                                "Geothermal",
                                "Radiant",
                                "Planet",
                                "Emission",
                                "Sizzle",
                                "Zap",
                                "Wave",
                                "Harvest",
                                "Air",
                                "Biomass",
                                "Carbon",
                                "Efficiency",
                                "Giga",
                                "Innovate",
                                "Mega",
                                "Neutron",
                                "Photon",
                                "Renewable",
                                "Revolve",
                                "Spark",
                                "Thermal",
                                "Vortex",
                                "Watt",
                                "Zero",
                                "PowerPunch",
                                "JoltJester",
                                "BatteryBanter",
                                "EnergeticLaughs",
                                "StorageSpark",
                                "ChargeChuckler",
                                "HumorHavoc",
                                "FunnyFuel",
                                "ZappyZingers",
                                "WittyWatt",
                                "EnergyVault",
                                "PowerCell",
                                "StorageSolutions",
                                "ChargeMaster",
                                "BatteryTech",
                                "PowerHub",
                                "EcoStorage",
                                "RenewableEnergy",
                                "EfficientEnergies",
                                "EnergyVault",
                                "PowerCell",
                                "StorageSolutions",
                                "ChargeMaster",
                                "BatteryTech",
                                "PowerHub",
                                "EcoStorage",
                                "RenewableEnergy",
                                "EfficientEnergies"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 4: { // Generate a name for Auto category
        vector<string> words = {
            "Speed",       "Drive",         "Auto",      "Wheel",      "Car",          "Turbo",      "Vroom",
            "Cruise",      "Road",          "Engine",    "Flash",      "Dom",          "OnTheRoad",  "Lightning",
            "Muskla",      "Sleek",         "Gizmo",     "Adrenaline", "Fuel",         "Bumper",     "Sprint",
            "Beep",        "Honk",          "Mile",      "Highway",    "Chassis",      "Rev",        "Piston",
            "Gear",        "Accelerate",    "Tyre",      "Brake",      "Transmission", "Steering",   "Ignition",
            "Convertible", "Stallion",      "Cruiser",   "Scooter",    "Gadget",       "Horsepower", "Dashboard",
            "Gearshift",   "Muscle",        "Auto",      "Toyopa",     "Honba",        "Niisan",     "Chevrolay",
            "Audio",       "Mercidez",      "BMX",       "Lexxus",     "Subaro",       "Kio",        "Cadillax",
            "Mitsubi",     "Folksvagen",    "Porshee",   "Jeep",       "Lambor",       "Bentleey",   "sherrari",
            "Rolling Roy", "Astton Lafite", "Mazdah",    "Volvo",      "Infinitii",    "Alfa Romeo", "Lexus",
            "Sloth",       "Land Hover",    "Lincollin", "GMC",        "Aubii",        "Buddatti",   "Maserahhi",
            "McLaren",     "Rage Rover"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 5: { // Generate a name for Banks category
        vector<string> words = {"Capital", "Trust",    "Secure",     "Savings",   "Finest",  "Elite",   "Prosper",
                                "Advance", "Global",   "Infinite",   "Vault",     "Wealth",  "First",   "Premier",
                                "Prime",   "Harmony",  "Velocity",   "Pinnacle",  "Noble",   "Fortune", "Evergreen",
                                "Summit",  "Frontier", "Excellence", "Sovereign", "Centric", "Vantage", "Opus",
                                "Paragon", "Zenith",   "Crest",      "Apex",      "Aegis",   "Legacy",  "Crown",
                                "Krupt",   "Meridian", "Encompass",  "Equity",    "Stellar", "Eclipse"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 6: { // Generate a name for Biotech category
        vector<string> words = {
            "GeneWorks",  "BioSolutions", "CellTech",      "InnoGene",   "BioGenius",    "VitaLab",    "BioFusion",
            "GeneSynth",  "EcoGene",      "LifeTech",      "BioMedix",   "GenoInnovate", "BioNova",    "GeneQuest",
            "BioSpark",   "InnoCell",     "BioRevolution", "GeneSense",  "BioVital",     "GeneXcel",   "BioMatrix",
            "GeneScribe", "InnoGene",     "BioNexus",      "GeneLink",   "BioTechne",    "SynthoGene", "GeneWave",
            "BioGenome",  "InnoBio",      "GenePrime",     "BioSpectra", "InnoCell",     "BioPlasma",  "GeneTech",
            "BioQuest",   "GeneGenius",   "InnoGene",      "BioCure",    "GeneCraft"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 7: { // Generate a name for Broadcast category
        vector<string> words = {
            "SoundBlast",     "MediaMania",        "EchoFiesta",     "ChannelChaos",     "AudioCircus",
            "GlobalGiggles",  "TalkTunes",         "Listen2Laughs",  "WaveWhimsy",       "LiveLaughs",
            "Listen2Me",      "StreamSmiles",      "VoiceVortex",    "RadioRuckus",      "BroadcastBanter",
            "SonicSilliness", "AudioAmusement",    "MediaMirth",     "TalkTickles",      "AudioWhoopee",
            "ListenUpLaughs", "StreamSilliness",   "SoundPulse",     "ChannelChuckles",  "RadioRoars",
            "VoiceVibe",      "EchoEntertainment", "AudioStreamers", "MediaLaughs",      "TalkTrek",
            "WaveWire",       "BroadcastBliss",    "SonicStreamers", "SoundSerendipity", "AudioAmusement",
            "ListenInLaughs", "StreamCenter",      "VoicePulse",     "RadioRadar",       "ChannelWave",
            "SoundSync",      "SoundWave",         "MediaCast",      "EchoStream",       "ChannelConnect",
            "AudioVision",    "GlobalBroadcast",   "TalkTime",       "Listen2me",        "WaveLink",
            "LiveAudio",      "StreamSquad",       "VoiceVortex",    "RadioRevolution",  "BroadcastHub",
            "SonicSignal",    "AudioSphere",       "MediaMingle",    "TalkBox",          "AudioWave",
            "ListenUp",       "StreamStation",     "SoundPulse",     "ChannelChatter",   "RadioRealm",
            "VoiceVibe",      "EchoChannel",       "AudioStream",    "MediaVox",         "TalkTrek",
            "WaveWire",       "BroadcastBox",      "SonicStream",    "SoundSphere",      "AudioMingle",
            "ListenIn",       "StreamCenter",      "VoicePulse",     "RadioRadar",       "ChannelWave",
            "SoundSync"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 8: { // Generate a name for Casinos&Gaming category
        vector<string> words = {"LuckyBets",
                                "GameGalore",
                                "SpinToWin",
                                "CasinoCraziness",
                                "JackpotJamboree",
                                "DiceyDelight",
                                "GamblingGiggles",
                                "CardComedy",
                                "WagerWhimsy",
                                "WinningLaughs",
                                "ChipsChuckles",
                                "PlayfulPoker",
                                "SlotSilliness",
                                "BingoBonanza",
                                "RouletteRiot",
                                "CasinoComedy",
                                "GamingGalore",
                                "BetBloopers",
                                "GamblingGalore",
                                "LaughingLottery",
                                "SpinSmiles",
                                "JokerJapes",
                                "BlackjackBliss",
                                "GameGiggles",
                                "LuckyLaughter",
                                "Splash of Clans",
                                "DiceDelirium",
                                "WagerWhoopee",
                                "CardCapers",
                                "WinningWhimsy",
                                "ChipsChortle",
                                "GTB VII",
                                "GTC V",
                                "HunterXHunter",
                                "PlayfulPoker",
                                "SlotSilliness",
                                "BingoBanter",
                                "RouletteRomp",
                                "CasinoChuckles",
                                "Monster Cooker World",
                                "GamingGalore",
                                "BetBloopers",
                                "GamblingGalore",
                                "LaughingLottery",
                                "SpinSniggers",
                                "Defence on Titan",
                                "LuckyCasino",
                                "GameCentral",
                                "SpinWin",
                                "CasinoHub",
                                "JackpotCity",
                                "Denshin Impact",
                                "Splash Royale",
                                "DiceGaming",
                                "GamblingClub",
                                "CardMaster",
                                "WagerZone",
                                "WinningStreak",
                                "Road Fighter XI",
                                "ChipsPalace",
                                "PlayfulGaming",
                                "SlotParadise",
                                "BingoEmpire",
                                "RouletteRealm",
                                "Sudoku",
                                "CasinoWorld",
                                "GamingZone",
                                "BetMasters",
                                "GamblingKingdom",
                                "LuckyLottery",
                                "Cooking Papa",
                                "SpinPalace",
                                "JokerCasino",
                                "BlackjackElite",
                                "GameMaster",
                                "LuckyWin",
                                "ForNight",
                                "WeCraft",
                                "DiceGaming",
                                "WagerZone",
                                "CardMaster",
                                "WinningStreak",
                                "ChipsPalace",
                                "Hokemon",
                                "PlayfulGaming",
                                "SlotParadise",
                                "BingoEmpire",
                                "RouletteRealm",
                                "CasinoWorld",
                                "MustLose",
                                "GuaranteedWin",
                                "GamingZone",
                                "BetMasters",
                                "GamblingKingdom",
                                "LuckyLottery",
                                "SpinPalace",
                                "Nario"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 9: { // Generate a name for E-Commerce category
        vector<string> words = {"Shopaholic",      "Buy-o-matic",
                                "DealDiva",        "CartoonCraze",
                                "SaleSensation",   "Hundredcents",
                                "Thousandcents",   "DiscountDelight",
                                "BargainBonanza",  "OnlineOlympics",
                                "ShipShop",        "PricelessPurchases",
                                "SkyDog",          "Bmazon",
                                "ClickComedy",     "eBayLaughs",
                                "AmazonAmusement", "ShoppingShenanigans",
                                "VirtualVortex",   "SaleSlapstick",
                                "Buyer'sBliss",    "DealDazzle",
                                "CartoonCapers",   "ShopSmart",
                                "SkyCat",          "BuyDirect",
                                "DealFinder",      "CartConnect",
                                "SaleSpot",        "DiscountMart",
                                "BargainHunt",     "OnlinePlaza",
                                "ShipRight",       "PricePoint",
                                "ClickCentral",    "eBayDeals",
                                "AmazonEmporium",  "ShoppingSolutions",
                                "VirtualMarket",   "SaleSolutions",
                                "Buyer'sParadise", "DealHaven",
                                "CartConnect"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 10: { // Generate a name for FinServices category
        vector<string> words = {"CashComedy",         "Dollar Dazzle",       "FinanceFunnies",     "WealthWhimsy",
                                "MoneyMaster",        "InvestmentLaughs",    "Savings Smiles",     "FunnyFunds",
                                "PennyPunchlines",    "BillsBanter",         "CapitalConsulting",  "WealthManagement",
                                "FinancialSolutions", "MoneyMatters",        "InvestmentAdvisors", "SecureBanking",
                                "SmartFunds",         "EconomicConsultancy", "FinancialExperts"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 11: { // Generate a name for Food&Beverage category
        vector<string> words = {
            "Tasty",   "Delicious", "Yummy",  "Flavorful", "Gourmet",  "Savor",     "Flavors",       "Satisfy",
            "Cuisine", "Culinary",  "Taste",  "Palate",    "Savoring", "Bites",     "Mouthwatering", "Bakery",
            "Cafe",    "Catering",  "Dining", "Juicy",     "Zesty",    "Fresh",     "Spice",         "Sip",
            "Brew",    "Crave",     "Snack",  "Seasoned",  "Saucy",    "Wholesome", "Nourish",       "Treats",
            "Feast",   "Chew",      "Munch",  "Appetite",  "Sip",      "Gobble",    "Gulp",          "Plate",
            "Yum",     "Morsel",    "Nibble", "Digest",    "Mouthful", "Bistro",    "Savor",         "Crunch",
            "Sizzle",  "Devour"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 12: { // Generate a name for Healthcare&Pharm category
        vector<string> words = {
            "Health",    "Wellness", "Care",   "Medical",  "Life",      "Apple/Day",  "Vital",
            "Active",    "Healthy",  "Cure",   "Recover",  "Pay4Med",   "Nourish",    "Thrive",
            "Restore",   "Revive",   "Fit",    "Strong",   "Balance",   "Medi",       "Pharma",
            "Sana",      "Sano",     "Salute", "Pulse",    "Vita",      "Healthcare", "Wellbeing",
            "Medic",     "Clinic",   "Well",   "Doctor",   "Nurse",     "Heal",       "Surgery",
            "Wellness",  "Rx",       "Pharm",  "Lab",      "Medical",   "Caring",     "Healing",
            "Rehab",     "Recovery", "Dose",   "MediCare", "Medix",     "Pharma",     "Pharmaceutical",
            "Medi",      "Health",   "Care",   "Wellness", "Rx",        "Med",        "Vita",
            "Sana",      "Sano",     "Salute", "Pulse",    "Pharmacy",  "Medicine",   "Drugs",
            "Wellbeing", "Cure",     "Heal",   "Remedy",   "Prescribe", "Relief",     "Recovery",
            "Dose",      "MediCare", "Medix",  "Healthy",  "Fit",       "Strong",     "Balance"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 13: { // Generate a name for Tech category
        vector<string> words = {"Tech",   "Digital", "Innovate", "Byte",  "Code",  "Data", "Logic",  "Connect",
                                "Smart",  "Cyber",   "Net",      "Cloud", "Web",   "Nerd", "Geek",   "Infinite",
                                "System", "Guru",    "Genius",   "Solve", "Pixel", "Bit",  "Invent", "KKGarden"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 14: { // Generate a name for RealEstate category
        vector<string> words = {"Real",        "Estate",   "Property",   "Homes", "Realty",      "Invest",
                                "Buy",         "Sell",     "House",      "Land",  "Residential", "Commercial",
                                "Development", "Build",    "Investment", "Acres", "Estates",     "Brokers",
                                "Agents",      "Mortgage", "Rent",       "Lease", "Property",    "Assets",
                                "Housing",     "Tower",    "Plaza",      "Villa", "Condo",       "Develop",
                                "Society",     "Park",     "Living",     "Urban", "Suburban"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 15: { // Generate a name for Retail category
        vector<string> words = {"Obsidian",    "Velvetine", "Stellar", "Luminary", "Nebula",    "Zephyr",   "Elixir",
                                "Intrigue",    "Sapphire",  "Crimson", "Aurora",   "Celestial", "Enigma",   "Mystique",
                                "Euphoria",    "Radiance",  "Galaxy",  "Harmonia", "Opulence",  "Ethereal", "Curio",
                                "Boutique",    "Ethereal",  "Nook",    "Vivid",    "Enchant",   "Whimsy",   "Delight",
                                "Serendipity", "Wander",    "Charm",   "Spruce",   "Eclectic",  "Rustic",   "Vintage"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    case 16: { // Generate a name for Telecom category
        vector<string> words = {"Connect", "Link",    "Wireless", "Tele",     "Net",     "Signal",   "Comm",
                                "Telecom", "Tech",    "Mobile",   "Global",   "Data",    "Wave",     "Teleconnect",
                                "Swift",   "Talk",    "Voice",    "Fiber",    "Reach",   "OnCall",   "Echo",
                                "Pulse",   "Synapse", "Velocity", "Empower",  "Amplify", "Momentum", "Infinite",
                                "Nexus",   "Stream",  "Sync",     "Telepath", "Radiant", "Blaze",    "Quantum"};

        for (unsigned int i = 0; i < num; i++) {
            string name = words[uniform_int_distribution<int>(0, words.size() - 1)(gen)] + " " +
                          suffixes[uniform_int_distribution<int>(0, suffixes.size() - 1)(gen)];
            if (find(companyNames.begin(), companyNames.end(), name) == companyNames.end())
                companyNames.push_back(name);
            else
                i--;
        }
        break;
    }
    default:
        /** "Group 88" is the fallback value for input category out of [0, sizeofCategoryList - 1] */
        return std::vector<std::string>(1, "Group 88");
        break;
    }
    return companyNames;
}
