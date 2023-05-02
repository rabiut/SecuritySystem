#include "motion_sensor.h"

int send_motion_sensor_data(const char *image_path, const char *info_text, const char *url)
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "image",
                     CURLFORM_FILE, image_path,
                     CURLFORM_END);

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "info_text",
                     CURLFORM_COPYCONTENTS, info_text,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("Request sent successfully.\n");
        }

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
    }

    curl_global_cleanup();
    return 0;
}
