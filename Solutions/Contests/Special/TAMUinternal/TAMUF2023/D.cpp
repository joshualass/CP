#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<string> board(n);
    for(auto &x: board) cin >> x;

    int try1 = 0;
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 'X') {
                cnt++;
            }
        }
        if(cnt & 1) try1++;
    }
    int try2 = 0;
    for(int i = 0; i < m; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if(board[j][i] == 'X') {
                cnt++;
            }
        }
        if(cnt & 1) try2++;
    }

    cout << max(try1, try2) << '\n';
    
    // int n, m; cin >> n >> m;

    // vector<string> board(n);

    // for(auto &x : board) cin >> x;

    // array<int,4> cnts = {0,0,0,0};

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         if(board[i][j] == 'X') {
    //             cnts[(i % 2) * 2 + j % 2]++;
    //         }
    //     }
    // }

    // cout << cnts[0] << " " << cnts[1] << " " << cnts[2] << " " << cnts[3] << '\n';

    // cout << (cnts[0] & 1) + (cnts[1] & 1) + (cnts[2] & 1) + (cnts[3] & 1) << '\n';

    return 0;
}

/*
MMMMMMMMNNNNNNNNNNNNNNNNNNmNNNNNNNNNNNmmmmmmmmNNMMMMNMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMNNMMMNMMMMMMMMMMMMMMMMMMMMMMNNMMNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMNNNNNNNNNNNmNNNMMMMMMMMMMMMNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMNNNNNNNNNNNNNNNNmmNNNNNNNNMMMMMMMMNmNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMNNNNNMMNNNNNNNNNNNNNNNNNNNNNMMMMMMMMNmNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMNNNNNMMNNNNNNmNNNNNNNMMMMMMMMMMMMMMMMNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMNNNNNNNNNNNNNmNNNNNNNNNNMMMMMMMMMMMMMMmMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMNNNNNNNNNNNNNmNNNmNMMMMmMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMNNNNNNNNNNmmmmmNNNNMMNMMNNMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
NNNNNNNNNNNmmmmdddddmNNNNMNNMMNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMNNMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
NNNNNNNNNmmmddddhhhdNNNmmMMMMNmmNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMNMMMMMMMMMNMMMMMMMMMMMMMMMNMMNMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
NNNNNNNNmmddddhhhhhdmNNmNmNNNNNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMMMMNMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMNMMMMMMMMMMMMMMMNMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMM
NNNNNNNmmddddhhhhhhhdNNmNNNNNNNNmmNNNNNNNNNNMMMMMMMMMMMMNMMNMMMMNMMMMMNMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMNMMMMMMMMMMMMMMNMNMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMM
NNNNNNNmddhhhhhhhyyyhmmNmmmNNMMMMNmNNNNNNNNNMMMMMMMMMMMNMMMNMMMMNMMMMNNMMMMNMMMNMMMMMMMMMMMMMMMMNMMNMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMNNMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMM
NNNNNNmdhhhhhhyyysssshmdmNMMNNNNNNNmmmmmmmmMMMMMMMMMMMMNMMMNMMMMMMMMMNNMMMMNMMMNMMMMMMMMMMMMMMMMNMMNMMMNMMMNMMMNMMMMMMMMNMMMMMMMMMMMMMMNMMMMMMNNNNNNNNNMMNNNNNNNNNNNNNNNMM
MNNNNmdhyyyyyyysssssssdNNNNNNNNNNNNNNNNNNNmMMMMMMMMMMMMNMMMNMMMNMMMMMNNMMMMNMMMMMMMMMMMMMMMMMMMMNMMNMMMNMMMNMMMMNMMMMMMMNNNNMMMMMMMMMMMNMMMMMMMmmmmmNNNNmmmmmmmmmmmmmmmNNN
MMNNmmdhsoooooooooooooohmNNNNNNNNNNNNNNNdNNMMMMMMMMMMMMNMMMNMMMNNMMMMNMNMMMNMMMMNMMMMMMMMMMMMMMMNMMNMMMNMMMNMMMMMNMMMMMMNNNMNNNMMMMMMMNmMMMMMMMmdddmmmdddddddddddddddddmmN
MNNmmmdhsooooooooooo++ooshmNNNNNNNNNNmhysNNMMMMMMMMMMMNNMMMNMMMNNMMMMNMNMMMNMMMMNMMMMMMMMMMMMMMNMMNMMMNMMMMNNNMMMNMMMMMMNNNMMMMNNMMNNNMdMMMMNMMNmddddddddddddhhhhhhhhddmmN
NmmddddhhhhhhhhhhhhyyyyyyyyhdddmmdddhsoosdNMMMMMMMMMMMNNMMMNMMMNNMMNNmNNMMMNNMMMNMMMMMMMMMMMMMMNMMNMMMNMNNmNMMMMMMNMMMMMMNNNMMmNNNNMMMMmNMMMNNMNmNNNNNNNNNNNmmmmmmmmmNNNMM
mmdddddddddddddddddddhhyyyyyyyhhhyyyoooosdNMMMMMMMMMMMNNMMMNMMMNNMMMMNMNmNNMNMMMNMMMMMMMMMMMMMNNMNNMMNNNNNNMMMMMMMMNMMMMMNMMNMMmNNMmmMmNNMMMMNMMNNNNNNNNNNNNNNNNNNNNNNMMMM
mmddddhdddddddddddddddhhhyyyhhhysssoooosshNMMMMMMMMMMMNNMMMNMMMNNMMMMNMMNMMNNmNNNmMMMMMMMMMMMMNMNmNNNNMMMNMMMMMMMMMMNMMMMNMMMNNMMMMNMNNMNMMMMNNMNNNNNNNNNNNNmmmNNNNNNMMMMM
dddddhhhdddddddddddddddhhhhhhysosyoooosmsyNMMMMMMMMMMMNNMMMNMMMMNNMMMdMNNNMMMNNMMmNMMMMMMMMMMNMMNNMMNMMMNNNMNMMMMMMMMNMMMNMMNNNNNMMMmNMMNMMMMMNNNNNNNNNNNNNNmmNNNNNNMMMMMM
dddddhhhddddddddddddddddhhhsoosyhooooodNssNMMMMMMMMMMMNNNMMNNMNmdhhysshmNNNNNMNNMNmMMMMMMMMMNNMNNMMNNNNmNNNmyhddmmNMMMNMMNMNmMNdNMMmNmNMNMMMMMNmMmNNNNNNMMNNNNNNNMMMMMMMMM
dddddhhhddddddddddddddddysoooyhho++o+sNmosNMMMMMMMMMMMNNNMNdyhhhho////oyssydmmMNNMNNMMMMMMMMNMMNMMMNNNmdhyso++oosssyddNNNNMmMMNMNmNNmMmNmMMMMMMmmNmNNNNNNNNNNNNMMMMMMMMMMM
hdddhhhhhhhddddddddddddsoooyhhho++ssodNmosMMMMMMMMMMMMmNmhddmNMNNy/////+mmy/hNMMMMMMMMMMMMMMMMMMMMMMNmsohdo:::::+mNNdhhmNNNNMMNmNNmNMMNmmMMMMMMNdNmmNNNNNNNNNNMMMMMMMMMMMM
hhhhhyyyhhhhhdddddddddh++shhhho++shooNMdoyMMMMMMMMMMMMmMNdMMMMN+yy+sss++oMMdsmMMMMMMMMMMMMMMMMMMMMMMmyhNhmh+oo++:+MMMMNdNmmNNNNNMMNNmNMdmNMMMMMMNdNmNNNNNNNNMMMMMMMMMMMMMM
hhhhhyyyyhhhhhddddddddy++hhhhs+/+ys+hNNyoyNMMMMMMMMMMMNMMNNMMMh-oshdddyy+NMMNhMMMMMMMMMMMMMMMMMMMMMMdNMM+/yyddhss:NMMMMNMmNMMMMMMMMMNmmdNNNMMMMMNmmNmmNNNMMMMMMMMMMMMMMMMM
hhhhyyyyyyyhhhhddddddhs++hhhy+/:+o+smNNoodMMMMMMMMMMMMNMMMmMMMh-yydhddhhoNMMMNMMMMMMMMMMMMMMMMMMMMMMMMMM/oyddddydoNMMMmNMNMMMMMMMMMMMNNmNNNNNNNNNNdmmmNNNMMMMMMMMMMMMMMMMM
hhhhyyyyyyyhhhhddddddhs++yyo+++///ohNNs+dmNNNNNNNMMMMNNMMMNmMMN/+dhdmmhmhMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMs+hhddhdmmMMMNNMMNNNNNNNNNNNNNNNNNNNNNNNNNmmNmNNMMMMMMMMMMMMMMMMMM
hhhyyyyyyyyhhhhhhhhdhhy//o+/+s////yhNy+yNmNNNNNNNNNNNNNMMMMNNMMNoodNNNdsmMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNohNNNmdyNMMNNMMMNNNNNNNNNNNNNNNNNNNNNNNNNmmmNmMMMMMMMMMMMMMMMMMMM
hhhyyyyyyyyyhhhhhhhhhhh+//+sho/::/hhs+yNNmNNNNNNNNNNNNNMMMMMNNNNNmhdmddMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMmdmmmmNNNNNNNNNmNNNNNNNNNNNNNNNNNNNNNNNNNmNmmNMMMMMMMMMMMMMMMMMM
hhhyyyyyhyyhhhhhhhhhhhhhhhhhh+/://+/+hNNNmNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNNNNNNNmNNNNNNNNNNNNNNNmNNNNNNNNNmNNmmMMMMMMMMMMMMMMNMMM
hhyyyyyyhhhhhhhhhhhhhhhhhhhho:/os//smNNNNmNNNNNNNNNNNNmNNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMNNMMMMMMMMMMMMMMMMMMMNNNNNNNNNNMNNmNNNNNNNNNNNNNNNmNNNNNNNNNNmNmmmMMMMMMMMMMNNMMMMM
hyyyyyyyhhhhhhhhhhhhhhhhhhho://hhyyNNNNNNmNNNNNNNNNNNNmNNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMNmMMMMMMMMMMMMMMMMMMNNNNNNNNNNNNNNdNNNNNNNNNNNNNNNmNNNNNNNNNNmMMmmNMMMMMMMMNNNMMMMM
yyyyyyyhhhhhhhhhhhhhhhhhhho/:/+hhhhNNNNNmmNNNNNNNNNNNNmNNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMNNNNNNNNNNNmmmdNNNNNNNNNNNNNNmmNNNNNNNNNNmNMMmmNMMMMMMMMMMMMMMM
yysyyyyhhhhhhhhhhhhhhhhhho::::ohhhdNNNNNmmNNNNNNNNNNNNmNNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNNNNNNmdNNNNNNNNNNNNNNmmNNmNNNNNNNNmMMNmmNMMMMMMMMMMMMMM
yssyyyyhhyyyyyhhhhhhhhhyo:/o::shhhdNNNNmNmNNNNNNNNNNNNyNNNNNNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNNNNmsNNNNNNNNNNNNNNmmNNmNNNNNNNNmNNNmmmNNMMMMMMMMMMMN
ssssssyyysssyyyyyyyyyyy+:/so::syyymNNNmmNdNNNNNNNNNNNNhdNNNNNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNNNNhsNNNNNNNNNNNNNNmNNNdNNNNNNNNmddddhmdNNNNNMNNNNNNN
oo++++oooooossssssssso/:/os/::+oosNNNNdNNdNNNNNNNNNNNNhymNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNNmyyNNNNNNNNNNNNNNmNNNdNNNNNNNNmyyyhhhmdmmmNNmmmmddd
++////++oosssssssssso::/sss:::+++yNNNdNNNdNNNNNNNNNNNNhhyNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNyyyNNNNNNNNNNNNNNdNNNmmmmmmmmmmhdhddddmdddddddhhhhh
////////+ossyysysss+::/ssss::+ssshmNmmNNNdNNNNNNNNNNNNhhhhNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNNNhhhymNNNNNNNNNNNmmdmmmmdmmmmmmmmdddddmddhddhhhhhhhhh
//:::--:/+ssyyyyys/--+ssssy:-+sssmmmdmmNmdNNNNNNNNNNNNyyhyyNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNhyhhymNNNmmmmmmmmmmymmmmdmmmmmmmmdhhddddhdyhhhhhhhhhh
///::---/+osssyys/--+ssyysy--+sssmmdmmmmmdmmmmmNmNNNmmhssyyymNNNNNNNNNNNNNNNNNNNNNmmmNmmNNmmmmmNNNNNNNNNNNNNNNNNNNNNhssyssmmmmmmmmmmmmmmydmmmhmmmmmmmmdhdddddhhdyyyyhhhhhh
///::--:/+osssss:-:osssssys--+ssymdmmmmdmhmmmmmmmmmmmmhyyyyyohmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNdyssssssmmmmmmmmmmmmmmshmmmhmmmmmmmddhddddhhyhhyyyyhhhhh
///::--:/osssso--:ssssssyys--+ssyddmmmdmmhmmmmmmmmmmmmhsssssosshmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNdyssssssssmmmmmmmmmmmmmmsymmmhdddddddddyddhhhhhhhyyyyhhhhh
///::--:/osss+--:sssssssyss--+soydmmmhmmmhmmmmmmmmmmmmhsssssossssydNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmhsssssosssssmmmmmmmmmmmmddosdddhdddddddddyhhhhhhyyyhsyyhhhhh
////:--:+oss/--/sssssssyyss--+sohdddhddddddmmmmmmmmmmmysssssosssssoshNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNdyosossssosssssddmddddddddddhoodddhhddddddddydhhhyyyyyysyyhhhhh
////:::/+os/../ssssssssysss--/osddddhdddddhdddddddddmdyssssoosssssoossydNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmysosssoossooooooodddddddddddddsoohdddyddddddhhyhhhhhyyyhsyshddddd
////:::/+o/../sssssssssssss--:sddddyddddddhdddddddddddyooooooooooooooo+syhmmmmmmmmmmmmmmmmmmmmmmmmmmmmhyy+oooooooooo+ooooodddddddddddddooohddhshhhhhhhhhyhhhhhhhhhssdmmmmm
++//:::/+/../sssssssssyssss--:hhddyhhdddddydddddddddddyoooooooooooo+oo+yyysydmmmmmmmmmmmmmmmmmmmmmmdyyyys+oooooo+ooo+oooosdddddddddddhhoo+yhhhshhhhhhhhhshhhhhyyyysyyddddd
++//::://../ssyyyyyysyyssss:.-hhhhyyhhdddyyhddddddddddyoooo+ooooooo+oo+sssysssyhdmmmmmmmmmmmmmmdhysssssso+oooooo+ooo+ooooshdddhhhhhhhhy+++yhhyohhhhhhhhhsyyyyysssysosyyhhh
+++/:://..:ssyyyyyyyyyyyyss/.-hhhsyyhhhhhyhyhhhhhhhddhyoooo+ooooooyhhyosssssssssssyhdmmmmmmdhyssssssssssoooo+ooo+o+++++++shhhhhhhhhhhhs+++shhsshhhhyyyyyossssssssyyosoyyhh
+++////..-ossyyyyyyyhyyyyyy+..shyyshhhhhhyhshhhhhhhhhhy++++++++ooddddddhssssssssssssssyhhysssssssssssoyhdddhyo++/++++++++shhhhhhhhhhhy++++syysoyyyyyyyyyosssssssssysooyyhh
+++///-..+ossyyyyyyyhhhhyyss..oyssyhhhhhhyhshhhhhhhhhhy++++/++++++/:/oyddyossssssssssssossssssssssssoydho+++sy++/++/+++++yhhhhhhhhhyys/+//syyooyyyyyyyyyosssssssssysossyhh
+++//-../ooossyyyyyyyhyyysyy-.:oysyyyyyyyyysyhhhhhhhhhy++++/++++--+oo/-+hdyssyyyyssoooooooooooossssshds--///::://++/++++/yyyyyyyyyyyy+////oyyooyyyyyyyysosssssssssyysooyyh
++++/...+ooossyyyyyyyyyyssyy/..ooyyyyyyysyyysyyyyyyyyyy+++//++++:yhddhs-:yhhhhhhhddhooooooooyhhhhhhhho-+hhhhhy://///////+yyyyyyyyyyys/////oyssoyssssssss+ssssssssssyy+osyy
////.``/+++ossyyyyyyyyyyosss+..+oyyyyyyyoyyysyyyyyyyyyy//////////yhhhhhy--:---:://shh+oooo+yhhs/:::::-+hhhhhh+//////////+yyyyyyyyyyyo/////osoyosssssssss+ssssssssyyyyoooyy
/::-``-///++oossssssyyyosssso..-ssssyyyyoyyyssyyyyyyyyy//////////ohhhhhhyssoooo+:..+hy+oo+yhy:.:oyhhyshhhhhyo://////////+yyyyyyyysss/////:osohosssssssss+yyyyyyyyyhhhhoohh
:::.``::://+++o++o++oo+osssss-.-ssssssssossssossssyyyyy+o+////////hhhhhhhhhhhhhhhs-.sy++++hs-.ohhhhhhhhhhyo+/:/:/://////osssssssssso::::::ssshossssssooooyyyyyyhhhhdmmo+hh
//:--:////+++oo+++///++osssss:.-ooosssssossssosssosssysossyyssossossyyyyyyyyyyyyyyo-/so+/ss:-oyyyyysyyyyy++/-:::////++o+osossssssss///////ooos+ooooooooo+syyyyyyyyyyddo+yh
*/