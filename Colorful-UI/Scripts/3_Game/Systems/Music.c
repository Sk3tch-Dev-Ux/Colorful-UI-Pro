modded class DynamicMusicPlayerRegistry
{
    protected override void RegisterTracksMenu()
	{
		m_TracksMenu = new array<ref DynamicMusicTrackData>();

		RegisterTrackMenu("DZNC_Music_Menu_SoundShader", true);
	}

	protected void RegisterTracksCredits()
	{
		m_TracksCredits = new array<ref DynamicMusicTrackData>();

		RegisterTrackCredits("Music_Menu_subtitles_remake_SoundSet");
	}

    protected void RegisterTracksTime()
	{
		m_TracksTime = new array<ref DynamicMusicTrackData>();

		//DAY
		RegisterTrackTime("Music_time_day_1_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_2_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_3_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_4_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_5_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_6_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_7_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		RegisterTrackTime("Music_time_day_8_SoundSet", DynamicMusicPlayerTimeOfDay.DAY);
		
        //NIGHT
		RegisterTrackTime("Music_time_night_1_SoundSet", DynamicMusicPlayerTimeOfDay.NIGHT);
		RegisterTrackTime("Music_time_night_2_SoundSet", DynamicMusicPlayerTimeOfDay.NIGHT);
		
        //DAWN
		RegisterTrackTime("Music_time_dawn_1_SoundSet", DynamicMusicPlayerTimeOfDay.DAWN);
		RegisterTrackTime("Music_time_dawn_2_SoundSet", DynamicMusicPlayerTimeOfDay.DAWN);
		
        //DUSK
		RegisterTrackTime("Music_time_dusk_1_SoundSet", DynamicMusicPlayerTimeOfDay.DUSK);
		RegisterTrackTime("Music_time_dusk_2_SoundSet", DynamicMusicPlayerTimeOfDay.DUSK);
		
        //UNSORTED (This can play at any time uncomment if you want)
		//RegisterTrackTime("Music_time_based_new_6_SoundSet", DynamicMusicPlayerTimeOfDay.ANY);
	}

    // (This is for contaminated zones but I dont really need it, you can add it if you want.)
    // protected void RegisterTracksLocationStatic()
	// {
	// 	m_TracksLocationStatic = new array<ref DynamicMusicTrackData>();
	// 	m_TracksLocationStaticPrioritized = new array<ref DynamicMusicTrackData>();
	// }

	// protected void RegisterTracksLocationDynamic()
	// {
	// 	m_TracksLocationDynamic = new array<ref DynamicMusicTrackData>();

	// 	RegisterTrackLocationDynamic("Music_loc_contaminated_day_SoundSet", DynamicMusicLocationTypes.CONTAMINATED_ZONE, DynamicMusicPlayerTimeOfDay.DAY);
	// 	RegisterTrackLocationDynamic("Music_loc_contaminated_night_SoundSet", DynamicMusicLocationTypes.CONTAMINATED_ZONE, DynamicMusicPlayerTimeOfDay.NIGHT);
	// }
}
	