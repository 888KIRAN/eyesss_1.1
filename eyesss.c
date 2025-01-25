//////////////////////////////////////////////////////////////////////////////
//code by KIRAN.......................................first date = 23.1.2024//       
//////////////////////////////////////////////////////////////////////////////
//  _______       ___    ___ _______   ________   ________   ________       //
// |\  ___ \     |\  \  /  /|\  ___ \ |\   ____\ |\   ____\ |\   ____\      //
// \ \   __/|    \ \  \/  / | \   __/|\ \  \___|_\ \  \___|_\ \  \___|_     //
//  \ \  \_|/__   \ \    / / \ \  \_|/_\ \_____  \\ \_____  \\ \_____  \    //
//   \ \  \_|\ \   \/  /  /   \ \  \_|\ \|____|\  \\|____|\  \\|____|\  \   //
//    \ \_______\__/  / /      \ \_______\____\_\  \ ____\_\  \ ____\_\  \  //
//     \|_______|\___/ /        \|_______|\_________\\_________\\_________\ //
//              \|___|/                  \|_________\|_________\|_________| //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

// İçerik yazdırma geri çağırma fonksiyonu
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) 
{
    size_t total_size = size * nmemb;
    fwrite(ptr, size, nmemb, stdout);  // Gelen veriyi terminale yazdır
    return total_size;
}

// Başlık yazdırma geri çağırma fonksiyonu
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata) 
{
    size_t total_size = size * nitems;
    printf("\033[0;41m[HEADER]\033[0m: %.*s", (int)total_size, buffer);  // Gelen başlığı terminale yazdır
    return total_size;
}

void writer_function(int argc, char const *argv[])
{
    CURL *curl;
    CURLcode res;

    // Curl'i başlat
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) 
    {

        // URL'yi ayarla (argv[1] ilk argümandır)
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        for (int i = 2; i < argc; i++)
        {
                // "-s" parametresi varsa, içerik çıktısını engelle
            if (strcmp(argv[i], "-s") == 0)
            {
               curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

            }
            // "-n" parametresi varsa, başlıkları yazdırma fonksiyonunu aktif et
            else if (strcmp(argv[i], "-n") == 0)
            {
               curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);  // Başlıkları yazdırmak için geri çağırma fonksiyonu set edilir
               curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, stdout);
            }
        }
            
        // İstek yap ve sonucu kontrol et
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) 
        {
            fprintf(stderr, "\033[0;41m[ERROR]\033[0m\033[1;44m There is an error in the domain name spelling %s\033[0m\n", curl_easy_strerror(res));
        }

        // Curl oturumunu kapat
        curl_easy_cleanup(curl);
    }

    // Curl'i temizle
    curl_global_cleanup();

}



int main(int argc, char const *argv[])//main functions
{
    if (argc < 2) 
    {
        fprintf(stderr,"\033[1;43m[WARNING]\033[0m\033[1;44mHow to do = %s  <URL> \033[0m\n", argv[0]);
        fprintf(stderr,"\033[1;43m[WARNING]\033[0m\033[1;44mEnter a   = %s  <help> \033[0m\n",argv[0]);//the error's stderr
        fprintf(stderr,"\033[1;42m[Usage]\033[0m\033[1;44m: %s <URL> [-s to suppress output] [-n to show headers]\033[0m\n", argv[0]);

        return 1;
    }
   
    writer_function(argc,argv);
    return 0;
}

