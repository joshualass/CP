#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
class BoxFilling {
public:
    long long getNumber(int sizeX, int sizeY, int sizeZ, int cubeX, int cubeY, int cubeZ) {
        long long res = 0;
        cubeX--; cubeY--; cubeZ--;

        //remove 3-D shells
        long long shellcnt = max(0, min(min(min(cubeX, sizeX - 2), min(cubeY, sizeY - 2)), min(cubeZ, sizeZ - 2)));
        res += 1LL * sizeX * sizeY * sizeZ - 1LL * (sizeX - shellcnt) * (sizeY - shellcnt) * (sizeZ - shellcnt);
        sizeX -= shellcnt, sizeY -= shellcnt, sizeZ -= shellcnt, cubeX -= shellcnt, cubeY -= shellcnt, cubeZ -= shellcnt;

        //now simulate 3-D
        int i = 0;
        while(sizeX != 1 && sizeY != 1 && sizeZ != 1) {
            if(i % 3 == 0) {
                if(cubeZ == 0) {
                    sizeZ = 1;
                    break;
                }
                sizeZ--;
                cubeZ--;
                res += 1LL * sizeX * sizeY;
            } else if(i % 3 == 1) {
                if(cubeY == 0) {
                    sizeY = 1;
                    break;
                }
                sizeY--;
                cubeY--;
                res += 1LL * sizeX * sizeZ;
            } else {
                if(cubeX == 0) {
                    sizeX = 1;
                    break;
                }
                sizeX--;
                cubeX--;
                res += 1LL * sizeY * sizeZ;
            }
            i++;
        }
        //remove 2-D shells
        if(cubeX && cubeY) {
            shellcnt = min(cubeX,cubeY);
            res += 1LL * sizeX * sizeY - 1LL * (sizeX - shellcnt) * (sizeY - shellcnt);
            cubeX -= shellcnt;
            cubeY -= shellcnt;
            sizeX -= shellcnt;
            sizeY -= shellcnt;
        } else if(cubeX && cubeZ) {
            shellcnt = min(cubeX,cubeZ);
            res += 1LL * sizeX * sizeZ - 1LL * (sizeX - shellcnt) * (sizeZ - shellcnt);
            cubeX -= shellcnt;
            cubeZ -= shellcnt;
            sizeX -= shellcnt;
            sizeZ -= shellcnt;
        } else if(cubeY && cubeZ) {
            shellcnt = min(cubeY,cubeZ);
            res += 1LL * sizeY * sizeZ - 1LL * (sizeY - shellcnt) * (sizeZ - shellcnt);
            cubeY -= shellcnt;
            cubeZ -= shellcnt;
            sizeY -= shellcnt;
            sizeZ -= shellcnt;
        }
        //now simulate 2-D
        i = 0;
        while(!(sizeX == 1 && sizeY == 1 || sizeX == 1 && sizeZ == 1 || sizeY == 1 && sizeZ == 1)) {
            if(i % 3 == 0 && sizeX > 1) {
                if(cubeY == 0 && cubeZ == 0) {
                    sizeZ = 1;
                    sizeY = 1;
                    break;
                }
                res += sizeX;
                sizeY = max(1, sizeY - 1);
                sizeZ = max(1, sizeZ - 1);
                cubeY = max(0, cubeY - 1);
                cubeZ = max(0, cubeZ - 1);
            } else if(i % 3 == 1 && sizeY > 1) {
                if(cubeX == 0 && cubeZ == 0) {
                    sizeX = 1;
                    sizeZ = 1;
                    break;
                }
                res += sizeY;
                sizeX = max(1, sizeX - 1);
                sizeZ = max(1, sizeZ - 1);
                cubeX = max(0, cubeX - 1);
                cubeZ = max(0, cubeZ - 1);
            } else if(i % 3 == 2 && sizeZ > 1) {
                if(cubeX == 0 && cubeY == 0) {
                    sizeX = 1;
                    sizeY = 1;
                    break;
                }
                res += sizeZ;
                sizeX = max(1, sizeX - 1);
                sizeY = max(1, sizeY - 1);
                cubeX = max(0, cubeX - 1);
                cubeY = max(0, cubeY - 1);
            }
            i++;
        }
        return res + max(max(cubeX,cubeY),cubeZ) + 1;
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg1;
  cin >> arg1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg3;
  cin >> arg3;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg4;
  cin >> arg4;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg5;
  cin >> arg5;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = BoxFilling();
  long long ret = c.getNumber(arg0, arg1, arg2, arg3, arg4, arg5);
  cout << ret;
}

// #include <iostream>
// #include <vector>
// #include <iomanip>
// #include <limits>
// using namespace std;

// // SOLUTION_BEGIN
// class BoxFilling {
// public:
//     long long getNumber(int sizeX, int sizeY, int sizeZ, int cubeX, int cubeY, int cubeZ) {
//         long long res = 0;
//         cubeX--; cubeY--; cubeZ--;
//         int i = 0;
//         while(sizeX != 1 && sizeY != 1 && sizeZ != 1) {
//             if(i % 3 == 0) {
//                 if(cubeZ == 0) {
//                     sizeZ = 1;
//                     break;
//                 }
//                 sizeZ--;
//                 cubeZ--;
//                 res += 1LL * sizeX * sizeY;
//             } else if(i % 3 == 1) {
//                 if(cubeY == 0) {
//                     sizeY = 1;
//                     break;
//                 }
//                 sizeY--;
//                 cubeY--;
//                 res += 1LL * sizeX * sizeZ;
//             } else {
//                 if(cubeX == 0) {
//                     sizeX = 1;
//                     break;
//                 }
//                 sizeX--;
//                 cubeX--;
//                 res += 1LL * sizeY * sizeZ;
//             }
//             i++;
//         }
//         cout << "3D Done\n";
//         cout << "sX : " << sizeX << " sY : " << sizeY << " sZ : " << sizeZ << " cX : " << cubeX << " cY : " << cubeY << " cZ : " << cubeZ << " res : " << res << '\n';
//         i = 0;
//         while(!(sizeX == 1 && sizeY == 1 || sizeX == 1 && sizeZ == 1 || sizeY == 1 && sizeZ == 1)) {
//             if(i % 3 == 0 && sizeX > 1) {
//                 if(cubeY == 0 && cubeZ == 0) {
//                     sizeZ = 1;
//                     sizeY = 1;
//                     break;
//                 }
//                 res += sizeX;
//                 sizeY = max(1, sizeY - 1);
//                 sizeZ = max(1, sizeZ - 1);
//                 cubeY = max(0, cubeY - 1);
//                 cubeZ = max(0, cubeZ - 1);
//             } else if(i % 3 == 1 && sizeY > 1) {
//                 if(cubeX == 0 && cubeZ == 0) {
//                     sizeX = 1;
//                     sizeZ = 1;
//                     break;
//                 }
//                 res += sizeY;
//                 sizeX = max(1, sizeX - 1);
//                 sizeZ = max(1, sizeZ - 1);
//                 cubeX = max(0, cubeX - 1);
//                 cubeZ = max(0, cubeZ - 1);
//             } else if(i % 3 == 2 && sizeZ > 1) {
//                 if(cubeX == 0 && cubeY == 0) {
//                     sizeX = 1;
//                     sizeY = 1;
//                     break;
//                 }
//                 res += sizeZ;
//                 sizeX = max(1, sizeX - 1);
//                 sizeY = max(1, sizeY - 1);
//                 cubeY = max(0, cubeY - 1);
//                 cubeX = max(0, cubeX - 1);
//             }
//             i++;
//         }
//         cout << "2D Done\n";
//         cout << "sX : " << sizeX << " sY : " << sizeY << " sZ : " << sizeZ << " cX : " << cubeX << " cY : " << cubeY << " cZ : " << cubeZ << " res : " << res << '\n';
//         return res + max(max(cubeX,cubeY),cubeZ) + 1;
//     }
// };
// // SOLUTION_END

// int main() {
//   int arg0;
//   cin >> arg0;
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//   int arg1;
//   cin >> arg1;
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//   int arg2;
//   cin >> arg2;
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//   int arg3;
//   cin >> arg3;
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//   int arg4;
//   cin >> arg4;
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//   int arg5;
//   cin >> arg5;
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//   auto c = BoxFilling();
//   long long ret = c.getNumber(arg0, arg1, arg2, arg3, arg4, arg5);
//   cout << ret;
// }

/*
3D Done
sX : 4 sY : 1 sZ : 5 cX : 2 cY : 0 cZ : 4 res : 40
2D Done
sX : 1 sY : 1 sZ : 2 cX : 0 cY : 0 cZ : 1 res : 56
58

3D Done
sX : 5 sY : 1 sZ : 5 cX : 3 cY : 0 cZ : 4 res : 35
2D Done
sX : 2 sY : 1 sZ : 1 cX : 0 cY : 0 cZ : 0 res : 58
59

*/