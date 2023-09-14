            cout << "r: " << r << " c: " << c << " dir: " << dir << "\n";
            while (lab[r][c] != 'A') {
                switch (dir) {
                    case 1:
                        ans.push_back('D');
                        r--;
                        break;
                    case 2:
                        ans.push_back('U');
                        r++;
                        break;
                    case 3:
                        ans.push_back('R');
                        c--;
                        break;
                    case 4:
                        ans.push_back('L');
                        c++;
                        break;
                }
                dir = parents[r][c];

                break;
            }