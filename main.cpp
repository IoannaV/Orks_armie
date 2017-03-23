#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <numeric>

struct Ork {
    int g;
    int h;
};

//std::basic_ostream<char>& operator << (std::basic_ostream<char>& stream, const Ork& ork) {
//    stream << "(" << ork.g << "," << ork.h << ")";
//    return stream;
//}

int dif(const Ork& ork_) {
    return ork_.g - ork_.h;
}

/*emplate<typename T>
void print_container (const T& vec) {
    std::cout << "[ ";
    for ( auto &x : vec) {
        std::cout << x << " ";
    }
    std::cout << " ]" <<std::endl;
}*/

int main() {
    std::vector<Ork> all_armie;
    int n, g, h;
    std::cin >> n >> g >> h;
    int x, y;
    while ( n --> 0 ) {
        std::cin >> x >> y ;
        all_armie.push_back({x,y});
    }

    if (g + h > all_armie.size()) {
        std::cout << "-1" << std::endl;
        return 1;
    }
    std::sort(all_armie.begin(), all_armie.end(),
              [](const Ork& lork, const Ork& rork)
    {return dif(lork) > dif(rork);}
    );
//    print_container(all_armie);

    auto first_bad_g = std::find_if(all_armie.begin(), all_armie.end(),
                                    [](const Ork& ork) {return ork.g <= ork.h;}
    );
 //   assert(first_bad_g != all_armie.end());

//    std::cout << "First bad grog" << *first_bad_g << std::endl;

    size_t count_of_good_grogs = (first_bad_g - all_armie.begin());

    if ( count_of_good_grogs < g) {
        first_bad_g += (g - count_of_good_grogs);

    }

    size_t count_of_good_hunters = all_armie.end() - first_bad_g;
    if ( count_of_good_hunters < h) {
        first_bad_g -= (h - count_of_good_hunters);
    }

    std::vector<Ork> grog(all_armie.begin(), first_bad_g);
    std::vector<Ork> headhunters(first_bad_g, all_armie.end());


    int power = std::accumulate(grog.begin(), grog.end(), 0, [](int sum, Ork& ork){
                                                                return sum + ork.g;
                                                              });

    power = std::accumulate(headhunters.begin(), headhunters.end(),
                            power, [](int sum, Ork& ork){
                                    return sum + ork.h;
                                   });

    std::cout << power << std::endl;
    //    print_container(grog);
    //    print_container(headhunters);
}

