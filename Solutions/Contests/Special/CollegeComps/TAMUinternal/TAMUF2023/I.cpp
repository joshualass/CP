#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<pair<int,bool>> v(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        char c; cin >> c;
        v[i].first = num;
        v[i].second = (c == 'C'); // 0 - legit, 1 - catfish
    }

    sort(v.begin(), v.end());

    vector<pair<int,bool>> upd;
    int prev = -1;
    for(int i = 0; i < n; i++) {
        if(prev == v[i].first) {
            if(v[i].second) {
                upd.pop_back();
                upd.push_back(v[i]);
            }
        } else {
            upd.push_back(v[i]);
        }
        prev = v[i].first;
    }

    int ans = 0;
    if(upd.front().second == 0) {
        ans += upd.front().first - 17;
    }
    for(int i = 0; i < upd.size() - 1; i++) {
        if(upd[i].second == 0 && upd[i+1].second == 0) {
            ans += upd[i+1].first - upd[i].first;
        } else if(upd[i].second == 0) {
            ans += (upd[i+1].first - upd[i].first + 1) / 2;
        } else if(upd[i+1].second == 0) {
            ans += (upd[i+1].first - upd[i].first - 1) / 2;
        }
    }

    if(upd.back().second == 0) {
        ans += (1 + 1e9 - upd.back().first);
    }

    cout << ans << '\n';

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