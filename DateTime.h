struct Time {
	short int _h;
    short int _m;
    short int _s;
};

struct Date {
	short int _d;
    short int _m;
    short int _y;
};

struct DateTime {
	Date _date;
    Time _time;
};

bool operator <= (const Date& D1, const Date& D2) {
    if (D1._y < D2._y) {
        return true;
    } else if (D1._y == D2._y) {
        if (D1._m < D2._m) {
            return true;
        } else if (D1._m == D2._m) {
            if (D1._d < D2._d) {
                return true;
            } else if (D1._d == D2._d) {
                return true;
            }
        }
    }
    return false;
}

bool operator <= (const Time& T1, const Time& T2) {
    if (T1._h < T2._h) {
        return true;
    } else if (T1._h == T2._h) {
        if (T1._m < T2._m) {
            return true;
        } else if (T1._m == T2._m) {
            if (T1._s < T2._s) {
                return true;
            } else if (T1._s == T2._s) {
                return true;
            }
        }
    }
    return false;
}

bool operator == (const Date& D1, const Date& D2) {
    return (D1._d == D2._d && D1._m == D2._m && D1._d == D2._d);
}

bool operator <= (const DateTime& DT1, const DateTime& DT2) {
    if (DT1._date <= DT2._date) return true;
    return (DT1._date == DT2._date) && DT1._time <= DT2._time;
}