#include "header.h"

using std::string;
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

int main() 
{
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    string response {};
    json jsonData {};
    float exchangeRate {};

    if (curl) {
        const char* url = "https://openexchangerates.org/api/latest.json?app_id=91f635eec4b947fa8a7d1c5db6a5d02d";
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Setup URL to fetch, handle response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        // Error Handling
        if (res != CURLE_OK) {
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // SUCCESS API CALL
            try {
                jsonData = json::parse(response);
                //std::cout << response << std::endl;

                std::cout << "Base currency: " << jsonData["base"] << std::endl;
                const auto& rates = jsonData["rates"];
                exchangeRate = jsonData["rates"]["EUR"].get<float>();
                std::cout << "USD to EUR exchange rates: " << rates["EUR"] << std::endl;

            } catch (const json::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize cURL. " << std::endl;
    }
    curl_global_cleanup();


    // Display information
    float euros { getUserInput("How many euros are you exchanging? ") };
    //float exchangeRate { getUserInput("What is the exchange rate? ") };

    const float euroRate = 1 / exchangeRate;
    float dollars = euros * euroRate;

    std::cout << euros << " euros at an exchange rate of " << std::fixed << std::setprecision(2) << exchangeRate << " is " << dollars << " U.S. dollars." << std::endl;

    return 0;
}