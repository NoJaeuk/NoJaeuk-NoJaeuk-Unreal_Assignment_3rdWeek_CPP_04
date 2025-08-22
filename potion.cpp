#include <iostream>
#include <vector>
#include <string>
#include <map>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    //포션 이름으로 검색하는 메서드
    PotionRecipe* searchRecipeByName(const std::string& name) {
        for (int i = 0; i < recipes.size(); i++) {
            if (recipes[i].potionName == name) {
                return &recipes[i];
            }
        }
        return nullptr;
    }
    
    //포션 재료로 검색하는 메서드
    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string ingredient) {
        std::vector<PotionRecipe> vector;
        for (int i = 0; i < recipes.size(); i++) {
            for (int j = 0; j < recipes[i].ingredients.size(); j++) {
                if (recipes[i].ingredients[j] == ingredient) {
                    vector.push_back(recipes[i]);
                }
            }
        }
        return vector;
    }

    //특정 레시피를 출력하는 메서드
    void displayRecipes(PotionRecipe recipe) const {
        std::cout << "- 물약 이름: " << recipe.potionName << std::endl;
        std::cout << "  > 필요 재료: ";

        // 재료 목록을 순회하며 출력
        for (size_t j = 0; j < recipe.ingredients.size(); ++j) {
            std::cout << recipe.ingredients[j];
            // 마지막 재료가 아니면 쉼표로 구분
            if (j < recipe.ingredients.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }


    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
        std::cout << "\n";
    }
};

//포션의 갯수를 관리하는 클래스
class StockManager {
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;

public:

    //포션의 초기값을 설정하는 함수
    void initializeStock(std::string potionName) {
        potionStock.insert({ potionName, MAX_STOCK });
    }

    //포션이 있으면 빼는 함수
    bool dispensePotion(std::string potionName) {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end() && potionStock[potionName] > 0) {
            potionStock[potionName]--;
            return true;
        }
        return false;
    }

    //공병을 반환받는 함수
    void returnPotion(std::string potionName) {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end()) {
            if (potionStock[potionName] == 3) {
                std::cout << "\n그 포션은 더이상 가질 수 없습니다.\n";
            }
            else
            {
                std::cout << "\n" << potionName << "을 반환받았습니다.\n";
                potionStock[potionName]++;
            }
        }
        else {
            std::cout << "\n존재하지 않는 포션입니다!\n";
        }
    }

    //포션이름으로 남은갯수 찾기
    int getStock(std::string potionName) {
        auto it = potionStock.find(potionName);
        if (it != potionStock.end()) {
            return potionStock[potionName];
        }
        else {
            return -1;
        }
    }


};





int main() {
    AlchemyWorkshop myWorkshop;
    StockManager myStockManager;

    while (true) {
        std::cout << "\n* 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 레시피 검색" << std::endl;
        std::cout << "3. 재고 검색" << std::endl;
        std::cout << "4. 포션 주기" << std::endl;
        std::cout << "5. 포션 반환" << std::endl;
        std::cout << "6. 모든 레시피 출력" << std::endl;
        std::cout << "7. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\n잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "\n물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
                myStockManager.initializeStock(name);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            std::cout << "\n찾으려는 레시피의 이름이나 재료를 입력해 주세요: ";
            std::string search;
            std::cin >> search;
            if (myWorkshop.searchRecipeByName(search) != nullptr) {
                std::cout << "포션 이름 : [" << search << "] 의 레시피 입니다\n";
                myWorkshop.displayRecipes(*myWorkshop.searchRecipeByName(search));
            }
            else if(!myWorkshop.searchRecipeByIngredient(search).empty()) 
            {
                std::cout << "포션 재료 : [" << search << "] 이(가) 들어가는 레시피 입니다\n";
                for (int i = 0; i < myWorkshop.searchRecipeByIngredient(search).size(); i++) {
                    myWorkshop.displayRecipes(myWorkshop.searchRecipeByIngredient(search)[i]);
                }
            }
            else {
                std::cout << "일치하는 레시피가 없습니다.\n";
            }
        }
        else if (choice == 3) {
            std::cout << "\n찾으려는 레시피의 이름이나 재료를 입력해 주세요: ";
            std::string find;
            std::cin >> find;
            if (myWorkshop.searchRecipeByName(find) != nullptr) {
                std::cout << "포션 이름 : [" << find << "] 의 재고 입니다\n";
                std::cout << myStockManager.getStock(find) << std::endl;
            }
            else if (!myWorkshop.searchRecipeByIngredient(find).empty())
            {
                std::cout << "포션 재료 : [" << find << "] 이(가) 들어가는 포션 재고 입니다\n";
                for (int i = 0; i < myWorkshop.searchRecipeByIngredient(find).size(); i++) {
                    myWorkshop.displayRecipes(myWorkshop.searchRecipeByIngredient(find)[i]);
                    std::cout << "재고 : " << myStockManager.getStock(myWorkshop.searchRecipeByIngredient(find)[i].potionName) << std::endl;
                }
            }
            else {
                std::cout << "일치하는 포션이 없습니다.\n";
            }


        }
        else if (choice == 4) {
            std::cout << "\n주려는 포션의 이름을 입력해 주세요: ";
            std::string find;
            std::cin >> find;
            if (myStockManager.dispensePotion(find)) 
            {
                std::cout << find << "을(를) 1개 지급했습니다.\n";
            }
            else { std::cout << "줄 포션이 없습니다.\n"; }

        }
        else if (choice == 5) {
            std::cout << "\n반환하려는 포션의 이름을 입력해 주세요: ";
            std::string find;
            std::cin >> find;
            myStockManager.returnPotion(find);
        }
        else if (choice == 6) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 7) {
            std::cout << "\n공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "\n잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}