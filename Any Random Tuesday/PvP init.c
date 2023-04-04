void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 1);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission : MissionServer {
    /*
     *  Config:
     *      This area is the only area in which users should change any information/variables.
     *      If you do not understand what something is being used for please read the comments above every function.
    */

    //Bag Name
    string bag_name = "AssaultBag_Ttsko";

    /*
     * Name: Assault Class
     * Primary Weapon: M4A1
     * Weapon Attachments: CQB Buttstock, ACOG Scope, RIS Handguard
     * Sidearm Weapon: IJ70
     * Sidearm Attachments: Suppressor
    */
    autoptr TStringArray Assault_Clothing = {"BallisticHelmet_UN", "USMCJacket_Desert", "CargoPants_Grey", "PressVest_Blue"};
    string Assault_Gun = "M4A1";
    string Assault_SideArm = "MakarovIJ70";
    autoptr TStringArray Assault_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Assault_Attachments = {"M4_CQBBttstck_Black", "ACOGOptic", "M4_RISHndgrd_Black"};
    autoptr TStringArray Assault_Mags = {"MAG_STANAG_30Rnd", "MAG_IJ70_8RND"}

    /*
     * Name: Submachine Gun Class
     * Primary Weapon: MP5K
     * Weapon Attachments: Rail Handguard, Buttstock, M69 Optic
     * Sidearm Weapon: IJ70
     * Sidearm Attachments: Suppressor
    */
    autoptr TStringArray Submachine_Clothing = {"BallisticHelmet_Green", "M65Jacket_Black", "CargoPants_Beige", "BalaclavaMask_Green", "PressVest_LightBlue"};
    string SubMachineGun_Gun = "MP5K";
    string SubMachineGun_Sidearm = "MakarovIJ70";
    autoptr TStringArray SubMachineGun_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray SubmachineGun_Attachments = {"MP5_PRailHndgrd", "MP5k_StockBttstck", "M68Optic"};
    autoptr TStringArray SubmachineGun_Mags = {"MAG_MP5_15Rnd", "MAG_IJ70_8RND"};

    /*
     * Name: Sniper Class
     * Primary Weapon: SVD
     * Weapon Attachments: PU Scope
     * Sidearm Weapon: IJ70
     * Sidearm Attachments: Suppressor
    */
    autoptr TStringArray Sniper_Clothing = {"BallisticHelmet_Black", "TShirt_Green", "NBCPantsYellow", "PoliceVest"};
    string Sniper_Gun = "SVD";
    string Sniper_Sidearm = "MakarovIJ70";
    autoptr TStringArray Sniper_SideArm_Attachments = {"MakarovPBSuppressor"};
    autoptr TStringArray Sniper_Attachments = {"PSO11Optic"};
    autoptr TStringArray Sniper_Mags = {"Mag_SVD_10Rnd", "MAG_IJ70_8RND"};

    /*
      * Name: Medic Class
      * Primary Weapon: FAL
      * Weapon Attachments: Fal_FoldingBttstck, ACOGOptic
      * Sidearm Weapon: IJ70
      * Sidearm Attachments: Suppressor
      * Medical Kit: Bandage, Morphine, Saline, Painkillers
     */
    autoptr TStringArray Medic_Clothing = {"BalaclavaMask_White", "ParamedicJacket_Crimson", "FirefightersPants_Black", "PlateCarrierVest"};
    string Medic_Gun = "FAL";
	string Medic_Sidearm = "MakarovIJ70";
	autoptr TStringArray Medic_Attachments = {"Fal_FoldingBttstck", "ACOGOptic"};
    autoptr TStringArray Medic_SideArm_Attachments = {"MakarovPBSuppressor"};
    string Medical_Supply_Case = "Firstaidkit";
    autoptr TStringArray Medical_Supplies = {"BandageDressing", "Morphine", "VitaminBottle", "Painkillertablets"};
    autoptr TStringArray Medic_Mags = {"Mag_FAL_20Rnd", "MAG_IJ70_8RND"};

    //  General Items which everyone will receive on spawn; regardless of class.
    autoptr TStringArray Utilities = {"TacticalBaconCan", "Canteen", "CanOpener", "BandageDressing", "M67Grenade", "RGD5Grenade", "Apple", "Flaregun", "Ammo_Flare", "Binoculars", "ChernarusMap"};
    autoptr TStringArray Uniform = {"LeatherGloves_Brown", "CombatBoots_Black"};

    // Melee Weapons
    autoptr TStringArray oneHanders = {"Machete", "HuntingKnife", "KitchenKnife", "Cleaver"};

    /*
     * End of Config:
     *   Do not change anything below unless you understand what you are doing....
    */

    autoptr TStringArray batteryCompatible = {"UniversalLight", "ReflexOptic", "M68Optic", "M4_T3NRDSOptic"};

    /*
     * @function addMags
     * @discussion Adds mags to players inventory
     *
     * @param    player: Instance Of Player
     * @param    magArray: Collection mag names
     * @param    count: Number of each mag which needs to be given.
     * @param    toQuickBar: Should be added to the quick bar, or not.
     */
    int magCount = 4;
    void addMags(PlayerBase player, TStringArray magArray, int count, bool toQuickBar) {
        if (count < 1 || magArray.Count() < 1)
            return;

        for(int x = 0; x < magArray.Count(); x++) {
            for (int i = 0; i < count; i++) {
                EntityAI mag = player.GetInventory().CreateInInventory(magArray.Get(x));
                if (toQuickBar)
                    if(x != 1) {
                        player.SetQuickBarEntityShortcut(mag, x + i + 2, true);
                    }else{
                        player.SetQuickBarEntityShortcut(mag, x + i + 3, true);
                    }
            }
        }
    }

    /*
     * @function dress_player
     * @abstract Gives player class related clothing.
     * @discussion This function puts choosen class clothing on the player.
     *
     * @param    player: Instance Of Player
     * @param    class_clothes: Collection of class clothing names
     * @param    general_items: Collection of general items which will also be given to the player
     */
    void dress_player(PlayerBase player, TStringArray class_clothes, TStringArray general_items){
        for(int i = 0; i < class_clothes.Count(); i++)
            player.GetInventory().CreateAttachment(class_clothes.Get(i));

        for(int x = 0; x < general_items.Count(); x++)
            player.GetInventory().CreateAttachment(general_items.Get(x));
    }
    
    /*
     *  @function   arm_player
     *  @abstract   Arms player with weapon, and adds attachments to weapon.
     *  @discussion This function creates a weapon, goes through all the attachments and attaches them,
     *                while checking if it needs a battery.
     *  @param      player: Instance of Player
     *  @param      weapon_name: Name of weapon to be given
     *  @param      gunAttachments: Collection of attachment names to be added to weapon
     *  @result     EntityAI: weapon
     */
    EntityAI arm_player(PlayerBase player, string weapon_name, TStringArray gunAttachments){
        EntityAI weapon = player.GetHumanInventory().CreateInHands(weapon_name);
        for(int i = 0; i < gunAttachments.Count(); i++){
            EntityAI attachment = weapon.GetInventory().CreateAttachment(gunAttachments.Get(i));
            for (int x = 0; x < batteryCompatible.Count(); x++){
                if(batteryCompatible.Get(x).Contains(gunAttachments.Get(i)))
                    attachment.GetInventory().CreateAttachment("Battery9V");
            }
        }
        return weapon;
    }

    EntityAI arm_player_secondary(PlayerBase player, string weapon_name, TStringArray secondaryAttachments){
        EntityAI weapon = player.GetInventory().CreateInInventory(weapon_name);
        for(int i = 0; i < secondaryAttachments.Count(); i++){
            EntityAI attachment = weapon.GetInventory().CreateAttachment(secondaryAttachments.Get(i));
            for (int x = 0; x < batteryCompatible.Count(); x++){
                if(batteryCompatible.Get(x).Contains(secondaryAttachments.Get(i)))
                    attachment.GetInventory().CreateAttachment("Battery9V");
            }
        }
        return weapon;
    }

    /*
     *  @function   give_utilities
     *  @discussion Added a backpack to the players back and fills it with provided items.
     *
     *  @param      player: Instance of Player
     *  @param      util: Collection of utility items names to be added to the backpack
     *  @param      backpack: Backpack item name which items will be stored, and will be added to players back.
     */
    void give_utilities(PlayerBase player, TStringArray util, string backpack){
        EntityAI backpackEnt = player.GetInventory().CreateAttachment(backpack);
        for (int i = 0; i < util.Count(); i++)
            backpackEnt.GetInventory().CreateInInventory(util.Get(i));
    }

    /*
    *  @function   give_medical
    *  @discussion Puts a bag into players inventory and adds items into the bag.
    *                  This is NOT the same as give_utilities, one adds bag to inventory, one adds bag to player.
    *  @param      player: Instance of Player
    *  @param      bag_name: Name of the bag which will be added to the players inventory and filled with items.
    *  @param      supplies: Collection of items which will be added to the bag.
    */
    void give_medical(PlayerBase player, string bag_name, TStringArray supplies) {
        EntityAI medickit = player.GetInventory().CreateInInventory(bag_name);

        for (int i = 0; i < supplies.Count(); i++)
            medickit.GetInventory().CreateInInventory(supplies.Get(i));
    }

    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName){
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
        Class.CastTo(m_player, playerEnt);

        GetGame().SelectPlayer(identity, m_player);

        return m_player;
    }

    override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {
        player.RemoveAllItems();

        EntityAI primary;
        EntityAI secondary;

        switch (Math.RandomInt(0, 4)) {
            case 0: // Assault
                dress_player(player, Assault_Clothing, Uniform);
                primary = arm_player(player, Assault_Gun, Assault_Attachments);
                secondary = arm_player_secondary(player, Assault_SideArm, Assault_SideArm_Attachments);
                give_utilities(player, Utilities, bag_name);
                addMags(player, Assault_Mags, magCount, true);
                break;
            case 1: // Sniper
                dress_player(player, Sniper_Clothing, Uniform);
                primary = arm_player(player, Sniper_Gun, Sniper_Attachments);
                secondary = arm_player_secondary(player, Sniper_Sidearm, Sniper_SideArm_Attachments);
                give_utilities(player, Utilities, bag_name);
                addMags(player, Sniper_Mags, magCount, true);
                break;
            case 2: // Submachine Gun
                dress_player(player, Submachine_Clothing, Uniform);
                primary = arm_player(player, SubMachineGun_Gun, SubmachineGun_Attachments);
                secondary = arm_player_secondary(player, SubMachineGun_Sidearm, SubMachineGun_SideArm_Attachments);
                give_utilities(player, Utilities, bag_name);
                addMags(player, SubmachineGun_Mags, magCount, true);
                break;
            case 3: // Medic
                dress_player(player, Medic_Clothing, Uniform);
                primary = arm_player(player, Medic_Gun, Medic_Attachments);
				secondary = arm_player_secondary(player, Medic_Sidearm, Medic_SideArm_Attachments);
                give_utilities(player, Utilities, bag_name);
                addMags(player, Medic_Mags, magCount, true);
                give_medical(player, Medical_Supply_Case, Medical_Supplies);
                break;
        }
        player.GetInventory().CreateInInventory(oneHanders.GetRandomElement());
        player.SetQuickBarEntityShortcut(primary, 0, true);

        if(secondary != null){
            player.SetQuickBarEntityShortcut(secondary, 1, true);
        }
    }
};

Mission CreateCustomMission(string path) {
    return new CustomMission();
}