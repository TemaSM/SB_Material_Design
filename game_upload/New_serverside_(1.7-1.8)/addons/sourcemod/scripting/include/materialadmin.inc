#if defined _materialadmin_included
  #endinput
#endif
#define _materialadmin_included

public SharedPlugin:__pl_materialadmin = 
{
	name = "materialadmin",
	file = "materialadmin.smx",
#if defined REQUIRE_PLUGIN
    required = 1
#else
    required = 0
#endif
};

#if !defined REQUIRE_PLUGIN
public __pl_materialadmin_SetNTVOptional()
{
	MarkNativeAsOptional("MAOffBanPlayer");
	MarkNativeAsOptional("MABanPlayer");
	MarkNativeAsOptional("MAUnBanPlayer");
	MarkNativeAsOptional("MAGetAdminExpire");
	MarkNativeAsOptional("MASetClientMuteType");
	MarkNativeAsOptional("MAOffSetClientMuteType");
	MarkNativeAsOptional("MAGetClientMuteType");
	MarkNativeAsOptional("MAGetConfigSetting");
	MarkNativeAsOptional("MAGetDatabaseConnect");
}
#endif

/*********************************************************
 * Получение хендель бд
 *********************************************************/
native Database MAGetDatabaseConnect();

/*********************************************************
 * Офлайн бан
 *
 * @param iClient	Клиент ид админа
 * @param sSteamID	Стим айди
 * @param sIp		Айпи
 * @param sName		Ник
 * @param iTime		Время (0 - навсегда) мин
 * @param sReason	Причина (можно указать в виде "")
 * @return			true, false
 *********************************************************/
native bool MAOffBanPlayer(int iClient, char[] sSteamID, char[] sIp, char[] sName, int iTime, char[] sReason);

/*********************************************************
 * Бан
 *
 * @param iClient	Клиент ид админа
 * @param iTarget	Клиент ид
 * @param iTime		Время (0 - навсегда) мин
 * @param sReason	Причина (можно указать в виде "")
 * @return			true, false
 *********************************************************/
native bool MABanPlayer(int iClient, int iTarget, int iTime, char[] sReason);

/*********************************************************
 * Разбан
 *
 * @param iClient	Клиент ид админа
 * @param sId		Айпи или Стим (в старом виде STEAM_)
 * @param sReason	Причина (можно указать в виде "")
 * @return			true, false
 *********************************************************/
native bool MAUnBanPlayer(int iClient, char[] sId, char[] sReason);

/*********************************************************
 * Временная админка
 *
 * @param idAdmin	Ид админа
 * @return			время в UNIX_TIMESTAMP
 *********************************************************/
native int MAGetAdminExpire(AdminId idAdmin);

#define MA_GAG			3
#define MA_MUTE			4
#define MA_SILENCE		5
#define MA_UNGAG		7
#define MA_UNMUTE		8
#define MA_UNSILENCE	9
/*********************************************************
 * Мут
 *
 * @param iClient	Клиент ид админа
 * @param iTarget	Клиент ид
 * @param iTime		Время (0 - навсегда) мин (При размуте можно указать 0)
 * @param sReason	Причина (можно указать в виде "")
 * @param iType		Тип (MA_GAG,MA_UNGAG - текстовый чат, MA_MUTE,MA_UNMUTE - голосовой чат, MA_SILENCE,MA_UNSILENCE - всё вместе)
 * @return			true, false
 *********************************************************/
native bool MASetClientMuteType(int iClient, int iTarget, int iTime, char[] sReason, int iType);

/*********************************************************
 * Оффлайн мут
 *
 * @param iClient	Клиент ид админа
 * @param sSteamID	Стим айди
 * @param sIp		Айпи (При размуте можно указать в виде "", но используется в логах)
 * @param sName		Ник	(При размуте можно указать в виде "", но используется в логах)
 * @param iTime		Время (0 - навсегда) мин (При размуте можно указать 0)
 * @param sReason	Причина (можно указать в виде "")
 * @param iType		Тип (MA_GAG,MA_UNGAG - текстовый чат, MA_MUTE,MA_UNMUTE - голосовой чат, MA_SILENCE,MA_UNSILENCE - всё вместе)
 * @return			true, false
 *********************************************************/
native bool MAOffSetClientMuteType(int iClient, char[] sSteamID, char[] sIp, char[] sName, int iTime, char[] sReason, int iType);

/*********************************************************
 * Узнать тип мута
 *
 * @param iClient	Клиент ид кого проверяем
 * @return 			0 - нету, 1 - голосовой чат, 2 - текстовый чат, 3 - всё вместе
 *********************************************************/
native int MAGetClientMuteType(int iClient);

/*********************************************************
 * Событие отключение голосовго или текстового чата
 * 
 * @param iClient	Клиент ид админа
 * @param iTarget	Клиент ид, если 0 - это оффлайн
 * @param sIp		Айпи 
 * @param sSteamID	Стим
 * @param sName		Ник
 * @param iType		Тип (1 - голосовой чат, 2 - текстовый чат, 3 - всё вместе)
 * @param iTime		Время
 * @param sReason	Причина 
 *********************************************************/
 forward void MAOnClientMuted(int iClient, int iTarget, char[] sIp, char[] sSteamID, char[] sName, int iType, int iTime, char[] sReason);
 
 /*********************************************************
 * Событие включение голосовго или текстового чата
 * 
 * @param iClient	Клиент ид админа
 * @param iTarget	Клиент ид, если 0 - это оффлайн
 * @param sIp		Айпи
 * @param sSteamID	Стим
 * @param sName		Ник
 * @param iType		Тип (1 - голосовой чат, 2 - текстовый чат, 3 - всё вместе)
 * @param iTime		Время
 * @param sReason	Причина
 *********************************************************/
 forward void MAOnClientUnMuted(int iClient, int iTarget, char[] sIp, char[] sSteamID, char[] sName, int iType, char[] sReason);

 /*********************************************************
 * Событие бана клиента
 * 
 * @param iClient	Клиент ид админа
 * @param iTarget	Клиент ид, если 0 - это оффлайн
 * @param sIp		Айпи
 * @param sSteamID	Стим
 * @param sName		Ник
 * @param iTime		Время
 * @param sReason	Причина
 *********************************************************/
 forward void MAOnClientBanned(int iClient, int iTarget, char[] sIp, char[] sSteamID, char[] sName, int iTime, char[] sReason);

 /*********************************************************
 * Событие добавление бана
 * 
 * @param iClient	Клиент ид админа
 * @param sIp		Бан айпи
 * @param sSteamID	Бан стима
 * @param iTime		Время
 * @param sReason	Причина
 *********************************************************/
 forward void MAOnClientAddBanned(int iClient, char[] sIp, char[] sSteamID, int iTime, char[] sReason);

 /*********************************************************
 * Событие разбана
 * 
 * @param iClient	Клиент ид админа
 * @param sIp		Разбан айпи
 * @param sSteamID	Разбан стима
 * @param sReason	Причина
 *********************************************************/
 forward void MAOnClientUnBanned(int iClient, char[] sIp, char[] sSteamID, char[] sReason);

 /*********************************************************
 * Получение настроек из конфига
 * Использовать тока в событие MAOnConfigSetting или после него, это примерно 2 секунды после запуска плагина или смены карты
 * 
 * @param sKey		Пишем сюда один из парамметров конфига
 * @param sValue	Возвращает сюда значение парамметра в строке, делайте строку не меньше 512 для получение больших значений
 * @return			true, false
 *********************************************************/
 native bool MAGetConfigSetting(char[] sKey, char[] sValue);
 
 /*********************************************************
 * Событие чтение конфига
 *********************************************************/
 forward void MAOnConfigSetting();