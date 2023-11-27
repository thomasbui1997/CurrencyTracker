#include "header.h"

using std::string;
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}


json makeApiCall(const char* url) 
{
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    string response {};

    if (curl) {
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
                return json::parse(response);
                
            } catch (const json::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize cURL. " << std::endl;
    }
    curl_global_cleanup();
    return json();
}


int main() 
{
    string response {};
    float exchangeRate {};

    const char* url {"https://openexchangerates.org/api/latest.json?app_id=91f635eec4b947fa8a7d1c5db6a5d02d"};
    json jsonData { makeApiCall(url) };

    std::cout << "Base currency: " << jsonData[0]["base"] << std::endl;
    const auto& rates = jsonData[0]["rates"];
    exchangeRate = jsonData[0]["rates"]["EUR"].get<float>();
    std::cout << "USD to EUR exchange rates: " << rates["EUR"] << std::endl;


    // Display information
    float euros { getUserInput("How many euros are you exchanging? ") };

    const float euroRate = 1 / exchangeRate;
    float dollars = euros * euroRate;

    std::cout << euros << " euros at an exchange rate of " << std::fixed << std::setprecision(2) << exchangeRate << " is " << dollars << " U.S. dollars." << std::endl;

    return 0;
}