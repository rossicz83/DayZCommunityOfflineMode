class CharacterLoad
{
    static PlayerBase LoadPlayer(string sCharacter, string sSave, bool bNoControl = false) {
        ref CharacterData oData = new CharacterData;

        JsonFileLoader<CharacterData>.JsonLoadFile(BASE_PLAYER_SAVE_DIR + "\\" + sCharacter + "\\" + sSave + ".json", oData);

		PlayerBase oPlayer;
		
		if ( bNoControl )
		{
			oPlayer = PlayerBase.Cast( GetGame().CreateObject( oData.SModel, "0 0 0", true ) );
		} else 
		{
			oPlayer = PlayerBase.Cast( GetGame().CreatePlayer( NULL, oData.SModel, "0 0 0", 0, "NONE") );
		}

        // Temporary for debugging purposes. Death checking not yet implemented.
        if (oData.FHealth < 20) oData.FHealth = 20;
        if (oData.FBlood < 2000) oData.FBlood = 2000;

		oPlayer.SetDirection( oData.VecDirection );
		oPlayer.SetOrientation( oData.VecOrientation );
        
		oPlayer.SetHealth("","", oData.FHealth );
		oPlayer.SetHealth("GlobalHealth", "Blood", oData.FBlood );
		oPlayer.GetStatBloodType().Set( oData.IBloodStatType );
		oPlayer.GetStatTemperature().Set( oData.FTemperature );
		oPlayer.GetStatEnergy().Set( oData.FEnergy );
		oPlayer.GetStatWater().Set( oData.FWater );
		oPlayer.GetStatStomachWater().Set( oData.FStomachWater );
		oPlayer.GetStatStomachEnergy().Set( oData.FStomachEnergy );
		oPlayer.GetStatHeatComfort().Set( oData.FHeatComfort );
		oPlayer.GetStatStomachSolid().Set( oData.FStomachSolid );
		oPlayer.GetStatWet().Set( oData.FWet );
		oPlayer.GetStatTremor().Set( oData.FTremor );
		oPlayer.GetStatStamina().Set( oData.FStamina );
		oPlayer.StatRegister("playtime");
		oPlayer.StatUpdate("playtime", oData.FPlayTime);
		oPlayer.SetLastShavedSeconds(oData.FLastShaved);
		oPlayer.SetBloodyHands(oData.FBloodyHands);

        if (oData.HasInventory) {
            InventoryLoad.Load(oPlayer, oPlayer, oData.OInventory);
        }

        if (oData.HasItemInHands) {
            HandLoad.Load(oPlayer, oPlayer, oData.OHands);
        }

		oPlayer.SetPosition( oData.VecPosition );

        return oPlayer;
    }
}