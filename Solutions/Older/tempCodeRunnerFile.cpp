        // for(int i = m - 1; i >= 0; m--) {
        //     for(int t = 0; t < 8; t++) { //given orientation t
        //         int most = 8;
        //         int index = 0;
        //         for(int s = 0; s < 3; s++) {
        //             int num = t ^ (1 << s);
        //             for(int f = 0; f < 8; f++) {
        //                 if(prefs[i][f] == flips[i+1][num]) {
        //                     if(f < most) {
        //                         most = i;
        //                         index = s;
        //                     }
        //                     break;
        //                 }
        //             }
        //         }
        //         flips[i][t] = t ^ index;
        //     }
        // }