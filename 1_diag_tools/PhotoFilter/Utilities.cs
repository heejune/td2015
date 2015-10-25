//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

using System.Linq;
using System.IO;

namespace PhotoFilter.WPF
{
    public static class Utilities
    {
        static string PhotoPathForUser = @"\Pictures";
        public static string[] ValidFileExtensions = new string[] { "jpg", "png" };

        public static string[] GetListOfFiles(string path)
        {
            return Directory.GetFiles(path);
        }
        
        public static bool IsValidImageFile(string file)
        {
            byte[] headerBytes;
            using (FileStream fileStream = new FileStream(file, FileMode.Open))
            {
                headerBytes = new byte[fileStream.Length];
                fileStream.Read(headerBytes, 0, (int) fileStream.Length);
            }

            //JPEG:
            if (headerBytes.Length > 10 && 
                headerBytes[0] == 0xFF &&//FF D8
                headerBytes[1] == 0xD8 &&
                (
                 (headerBytes[6] == 0x4A &&//'JFIF'
                  headerBytes[7] == 0x46 &&
                  headerBytes[8] == 0x49 &&
                  headerBytes[9] == 0x46)
                  ||
                 (headerBytes[6] == 0x45 &&//'EXIF'
                  headerBytes[7] == 0x78 &&
                  headerBytes[8] == 0x69 &&
                  headerBytes[9] == 0x66)
                ) &&
                headerBytes[10] == 00)
            {
                return true;
            }
            //PNG 
            if (headerBytes.Length > 7 &&
                headerBytes[0] == 0x89 && //89 50 4E 47 0D 0A 1A 0A
                headerBytes[1] == 0x50 &&
                headerBytes[2] == 0x4E &&
                headerBytes[3] == 0x47 &&
                headerBytes[4] == 0x0D &&
                headerBytes[5] == 0x0A &&
                headerBytes[6] == 0x1A &&
                headerBytes[7] == 0x0A)
            {
                return true;
            }
            //GIF
            if (headerBytes.Length > 2 &&
                headerBytes[0] == 0x47 &&//'GIF'
                headerBytes[1] == 0x49 &&
                headerBytes[2] == 0x46)
            {
                return true;
            }
            //BMP
            if (headerBytes.Length > 1 && 
                headerBytes[0] == 0x42 &&//42 4D
                headerBytes[1] == 0x4D)
            {
                return true;
            }
            //TIFF
            if (headerBytes.Length > 3 &&
                (headerBytes[0] == 0x49 &&//49 49 2A 00
                 headerBytes[1] == 0x49 &&
                 headerBytes[2] == 0x2A &&
                 headerBytes[3] == 0x00)
                 ||
                (headerBytes[0] == 0x4D &&//4D 4D 00 2A
                 headerBytes[1] == 0x4D &&
                 headerBytes[2] == 0x00 &&
                 headerBytes[3] == 0x2A))
            {
                return true;
            }

            return false;
        }

        public static bool IsValidImageExtension(string file)
        {

            var fileParts = file.Split('.');
            if (fileParts.Length < 2)
            {
                return false;
            }

            var extension = fileParts[fileParts.Length - 1];

            if (ValidFileExtensions.Contains(extension))
            {
                return true;
            }

            return false;
        }

        #region APIs
        public static string CurrentUser
        {
            get
            {
                string userName = System.Security.Principal.WindowsIdentity.GetCurrent().Name;
                if (userName.Contains("\\"))
                {
                    string[] strs = userName.Split('\\');
                    userName = strs[1];
                }
                return userName;
            }
        }

        public static string PhotoPath
        {
            get
            {
                string photoPath = @"C:\users\" + Utilities.CurrentUser + PhotoPathForUser;

                return photoPath;
            }
        }
        #endregion

    }
}
