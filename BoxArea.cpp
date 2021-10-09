#include "BoxArea.h"

BoxArea::BoxArea(){
}

BoxArea::BoxArea(double up, double low, double lft, double rght) : upper(up), lower(low),
                                                                    left(lft), right(rght){
}

BoxArea::BoxArea(const BoxArea& other) : upper(other.upper), lower(other.lower),
                                        left(other.left), right(other.right){
}

BoxArea::BoxArea(BoxArea&& other) : upper(other.upper), lower(other.lower),
    left(other.left), right(other.right) {
    other.left = other.right = other.lower = other.upper = 0;
}

bool BoxArea::is_in(double x, double y) const{
    return (x >= left && x <= right && y >= lower && y <= upper);
}
