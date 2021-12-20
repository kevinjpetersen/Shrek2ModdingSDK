using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shrek2ModManager
{
    public class Shrek2Utils
    {
        public const string SHREK2MM_FILE_ADDED_MODS = "added_mods.json";
        public const string SHREK2MM_FILE_SETTINGS = "settings.json";
        public const string SHREK2MM_FILE_LOG_ERRORS = "log_errors.txt";
        public const string SHREK2MM_FILE_MOD_LOADER_ZIP = "Shrek2ModLoader.zip";

        public const string SHREK2MM_MODLOADER_FILE_EXE = "Shrek 2 Modded.exe";
        public const string SHREK2MM_MODLOADER_FILE_INT = "Shrek 2 Modded.int";
        public const string SHREK2MM_MODLOADER_FILE_DLL = "Shrek2ModLoader.dll";
        public const string SHREK2MM_DEF_USER_FILE = "DefUser.ini";
        public const string SHREK2MM_DEF_USER_BACKUP_FILE = "Backup_DefUser.ini";

        public const string SHREK2MM_FOLDER_ADDED_MODS = "Added mods";
        public const string SHREK2MM_FOLDER_GAME_SYSTEM = "System";
        public const string SHREK2MM_FOLDER_GAME_SYSTEM_MODS = "Shrek 2 Mods";

        public static string GetDataFolderPath()
        {
            return Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "Shrek 2 Mod Manager");
        }

        public static string GetModLoaderZipFilePath()
        {
            return Path.Combine(GetDataFolderPath(), SHREK2MM_FILE_MOD_LOADER_ZIP);
        }

        public static string GetAddedModsFolderPath()
        {
            return Path.Combine(GetDataFolderPath(), SHREK2MM_FOLDER_ADDED_MODS);
        }

        public static string GetModdedGameExeFilePath(string gameFolderPath)
        {
            return Path.Combine(gameFolderPath, SHREK2MM_FOLDER_GAME_SYSTEM, SHREK2MM_MODLOADER_FILE_EXE);
        }

        public static string GetGameSystemFolderPath(string gameFolderPath)
        {
            return Path.Combine(gameFolderPath, SHREK2MM_FOLDER_GAME_SYSTEM);
        }

        public static string GetGameSystemModsFolderPath(string gameFolderPath)
        {
            return Path.Combine(gameFolderPath, SHREK2MM_FOLDER_GAME_SYSTEM, SHREK2MM_FOLDER_GAME_SYSTEM_MODS);
        }

        public static void EnsureDataFolderExists()
        {
            try
            {
                var path = GetDataFolderPath();
                if (!Directory.Exists(path)) Directory.CreateDirectory(path);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
        }

        public static void EnsureAddedModsFolderExists()
        {
            try
            {
                EnsureDataFolderExists();

                var path = Path.Combine(GetDataFolderPath(), SHREK2MM_FOLDER_ADDED_MODS);
                if (!Directory.Exists(path)) Directory.CreateDirectory(path);
            }
            catch (Exception ex)
            {
                LogError(ex);
            }
        }

        public static void LogError(Exception ex)
        {
            try
            {
                if (ex == null) return;
                LogErrorConsole(ex);
                LogErrorDisk(ex);

            }
            catch (Exception ex2)
            {
                LogErrorConsole(ex2);
            }
        }

        public static void LogErrorConsole(Exception ex)
        {
            try
            {
                if (ex == null) return;
                Debug.WriteLine($"{ex.Message}, {ex.StackTrace}");
            }
            catch { }
        }

        public static void LogErrorDisk(Exception ex)
        {
            try
            {
                if (ex == null) return;

                var errors = new List<string>
                {
                    $"[ERROR] [{DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture)}] {ex.Message}, {ex.StackTrace}"
                };

                File.AppendAllLines(Path.Combine(GetDataFolderPath(), SHREK2MM_FILE_LOG_ERRORS), errors);
            }
            catch (Exception ex2)
            {
                LogErrorConsole(ex2);
            }
        }
    }
}
