#include "misc_panel.h"

MiscPanel::MiscPanel (Vector2D position, Vector2D size)
	: Panel::Panel (position, size)
{
	ba_movement = new Banner ("Movement", LOC (10, 10), (size.x - 20) / 2 - 5);
	ts_bhop = new ToggleSwitchTip ("Bunny Hop", BELOW (ba_movement), LOC((size.x - 20) / 6.75, 30), &Settings::BHop::enabled, "Enables or disables auto bunny hopping");
	ts_autostrafe = new ToggleSwitchTip ("Auto Strafe", STACK (ts_bhop), LOC((size.x - 20) / 6.75, 30), &Settings::AutoStrafe::enabled, "Auto strafe when bunny hopping");
	ts_airstuck = new ToggleSwitchTip ("Air Stuck", BELOW (ts_bhop), LOC((size.x - 20) / 6.75, 30), &Settings::Airstuck::enabled, "Sticks you in the air when activated, for use to spawn in enemy base");
	kb_airstuck_key =  new KeyBind ("", STACK (ts_airstuck), LOC((size.x - 20) / 6.75, 30),  &Settings::Airstuck::key);
#ifdef UNTRUSTED_SETTINGS
	ts_teleport = new ToggleSwitchTip ("Teleport", BELOW (ts_airstuck), LOC((size.x - 20) / 6.75, 30), &Settings::Teleport::enabled, "Teleport. DONT USE ON VOLVO SERVERS");
	kb_teleport_key =  new KeyBind ("", STACK (ts_teleport), LOC((size.x - 20) / 6.75, 30),  &Settings::Teleport::key);
	ba_spammer = new Banner ("Spammer", BELOW (ts_teleport), (size.x - 20) / 2 - 5);
#else
	ba_spammer = new Banner ("Spammer", BELOW (ts_airstuck), (size.x - 20) / 2 - 5);
#endif
	ts_position_spammer = new ToggleSwitchTip ("Position Spammer", BELOW (ba_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::PositionSpammer::enabled, "Spams enemy position in chat");
	ts_position_spammer_say_team = new ToggleSwitchTip ("Team Chat", STACK (ts_position_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::PositionSpammer::say_team, "Spams enemy position in team chat");
	ts_kill_spammer = new ToggleSwitchTip ("Kill Spammer", BELOW (ts_position_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::KillSpammer::enabled, "Spams a kill message in chat");
	ts_kill_spammer_say_team = new ToggleSwitchTip ("Team Chat", STACK (ts_kill_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::KillSpammer::say_team, "Spams a kill message in team chat");
	ts_normal_spammer = new ToggleSwitchTip ("Chat Spammer", BELOW (ts_kill_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::NormalSpammer::enabled, "Spams random messages into chat");
	ts_normal_spammer_say_team = new ToggleSwitchTip ("Team Chat", STACK (ts_normal_spammer), LOC((size.x - 20) / 6.75, 30), &Settings::Spammer::NormalSpammer::say_team, "Spams random messages into team chat");
	ba_other = new Banner ("Other", STACK (ba_movement), (size.x - 20) / 2 - 5);
	ts_noflash = new ToggleSwitchTip ("No Flash", BELOW (ba_other), LOC((size.x - 20) / 6.75, 30), &Settings::Noflash::enabled, "Whether flashes effect you or not");
	sl_noflash_value = new Slider ("", STACK (ts_noflash), LOC ((size.x / 2) - ts_noflash->size.x - 30, 30), &Settings::Noflash::value, 0.0f, 255.0f);
	ts_fov = new ToggleSwitchTip ("View FOV", BELOW (ts_noflash), LOC((size.x - 20) / 6.75, 30), &Settings::FOVChanger::enabled, "Changes fov to beyond or below normal levels");
	sl_fov_value = new Slider ("", STACK (ts_fov), LOC ((size.x / 2) - ts_fov->size.x - 30, 30), &Settings::FOVChanger::value, 0.0f, 180.0f);
	ts_fov_viewmodel = new ToggleSwitchTip ("Viewmodel FOV", BELOW (ts_fov), LOC((size.x - 20) / 6.75, 30), &Settings::FOVChanger::viewmodel_enabled, "Changes viewmodel fov to beyond or below normal levels");
	sl_fov_viewmodel_value = new Slider ("", STACK (ts_fov_viewmodel), LOC ((size.x / 2) - ts_fov_viewmodel->size.x - 30, 30), &Settings::FOVChanger::viewmodel_value, 0.0f, 360.0f);
	ts_fakelag = new ToggleSwitchTip ("Fake Lag", BELOW (ts_fov_viewmodel), LOC((size.x - 20) / 6.75, 30), &Settings::FakeLag::enabled, "Adds fake lag to appear laggier");
	sl_fakelag = new Slider_INT ("", STACK (ts_fakelag), LOC ((size.x / 2) - ts_fakelag->size.x - 30, 33), &Settings::FakeLag::value, 0, 16);
	ts_radar = new ToggleSwitchTip ("Radar", BELOW (ts_fakelag), LOC((size.x - 20) / 6.75, 30), &Settings::Radar::enabled, "Show enemies on the radar");
	ts_showranks = new ToggleSwitchTip ("Show Ranks", BELOW (ts_radar), LOC((size.x - 20) / 6.75, 30), &Settings::ShowRanks::enabled, "Shows peoples ranks in a valve server");
	ts_showspectators = new ToggleSwitchTip ("Show Spectators", STACK (ts_showranks), LOC((size.x - 20) / 6.75, 30), &Settings::ShowSpectators::enabled, "Shows who is spectating you");
	ts_clantag = new ToggleSwitchTip ("Custom Clantag", BELOW (ts_showranks), LOC((size.x - 20) / 6.75, 30), &Settings::ClanTagChanger::enabled, "Set a custom clantag");
	tb_clantag = new TextBox ("Clantag", &Settings::ClanTagChanger::value, STACK (ts_clantag), LOC((size.x - 20) / 6.75, 30));
	ts_clantag_animation = new ToggleSwitchTip ("Clantag Animation", BELOW (ts_clantag), LOC((size.x - 20) / 6.75, 30), &Settings::ClanTagChanger::animation, "Sets the clantag to be animated");
	vtb_nickname = new ValueTextBox ("Nickname", "", BELOW (ts_clantag_animation), LOC((size.x - 20) / 6.75, 30));
	ob_nickname = new OutlinedButton ("Set Nickname", STACK (vtb_nickname), LOC((size.x - 20) / 6.75, 30));
	ob_nickname->OnClickedEvent = MFUNC (&MiscPanel::ob_nickname_clicked, this);
	ob_noname = new OutlinedButton ("No Name", BELOW (vtb_nickname), LOC((size.x - 20) / 6.75, 30));
	ob_noname->OnClickedEvent = MFUNC (&MiscPanel::ob_noname_clicked, this);
	ba_colors = new Banner ("Colors", BELOW (ob_noname), (size.x - 20) / 2 - 5);
	int x_wide = ba_colors->size.x / 4;
	bn_ui_color = new OutlinedButton ("Main UI", BELOW (ba_colors), LOC((size.x - 20) / 6.75, 30));
	bn_ui_color->OnClickedEvent = MFUNC (&MiscPanel::bn_ui_color_clicked, this);
	bn_2_color = new OutlinedButton ("X", STACK (bn_ui_color), LOC((size.x - 20) / 6.75, 30));
	bn_3_color = new OutlinedButton ("XX", STACK (bn_2_color), LOC((size.x - 20) / 6.75, 30));

	AddComponent (bn_3_color);
	AddComponent (bn_2_color);
	AddComponent (bn_ui_color);
	AddComponent (ba_colors);
	AddComponent (ob_noname);
	AddComponent (ob_nickname);
	AddComponent (ob_nickname);
	AddComponent (vtb_nickname);
	AddComponent (ts_clantag_animation);
	AddComponent (tb_clantag);
	AddComponent (ts_clantag);
	AddComponent (ts_showspectators);
	AddComponent (ts_showranks);
	AddComponent (ts_radar);
	AddComponent (sl_fakelag);
	AddComponent (ts_fakelag);
	AddComponent (sl_fov_viewmodel_value);
	AddComponent (ts_fov_viewmodel);
	AddComponent (sl_fov_value);
	AddComponent (ts_fov);
	AddComponent (sl_noflash_value);
	AddComponent (ts_noflash);
	AddComponent (ba_other);
	AddComponent (ts_normal_spammer_say_team);
	AddComponent (ts_normal_spammer);
	AddComponent (ts_kill_spammer_say_team);
	AddComponent (ts_kill_spammer);
	AddComponent (ts_position_spammer_say_team);
	AddComponent (ts_position_spammer);
	AddComponent (ba_spammer);
#ifdef UNTRUSTED_SETTINGS
	AddComponent(kb_teleport_key);
	AddComponent (ts_teleport);
#endif
	AddComponent(kb_airstuck_key);
	AddComponent (ts_airstuck);
	AddComponent (ts_autostrafe);
	AddComponent (ts_bhop);
	AddComponent (ba_movement);


	Hide ();
}

void MiscPanel::ob_nickname_clicked ()
{
	std::string name = std::string(vtb_nickname->text);
	Util::StdReplaceStr(name, "\\n", "\n");

	NameChanger::SetName(name.c_str());
}

void MiscPanel::ob_noname_clicked ()
{
	NameChanger::changes = -1;
	Settings::NameChanger::enabled = true;
	Settings::NameChanger::last_blank = true;
}

void MiscPanel::bn_ui_color_clicked ()
{
	static PopupColorWindow* wn_pop_color = new PopupColorWindow ("UI Main Color", LOC(420, 270), LOC(100,100), Color(0, 0, 0, 0), &Settings::UI::mainColor);


	if (!wn_pop_color->IsShown())
	{
		gui->AddWindow (wn_pop_color);
		wn_pop_color->OnShown ();
		wn_pop_color->Show ();
	}
	else
	{
		wn_pop_color->Destroy ();
	}
}
