// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     auto f = [&](ld x, ld a) -> ld {
//         return a * x * x * (1 - x);
//     };

//     ld a = 5;
//     ld x = 0.2;

//     cout << "0.2" << '\n';

//     for(int i = 0; i < 10; i++) {
//         cout << fixed << setprecision(10) << x << '\n';
//         x = f(x, a);
//     }

//     x = 0.5;

//     cout << "0.5\n";

//     for(int i = 0; i < 100; i++) {
//         cout << fixed << setprecision(10) << x << '\n';
//         x = f(x, a);
//     }

//     return 0;
// }


x(1)=1;
y(1)=1;

N=100;

%% -------- Case (i) --------
a1=0.5; a2=0.8; r1=0.2; r2=0.5;

f = @(x,y) a1*x + r1*y;
g = @(x,y) a2*y + r2*x;

n=1;
while n<N
    x(n+1)=f(x(n),y(n));
    y(n+1)=g(x(n),y(n));
    n=n+1;
end

plot(x)
hold on
plot(y)
xlabel('n')
ylabel('x_n, y_n')
legend('x_n','y_n')
set(gca,'fontsize',16)
set(gca,'fontweight','bold')

figure
plot(x,y,'o-')   % <-- dots added
xlabel('x_n')
ylabel('y_n')
set(gca,'fontsize',16)
set(gca,'fontweight','bold')

clear x y



clear; clc; close all

% parameters (i)
a1=0.5; 
a2=0.8; 
r1=0.2; 
r2=0.5;

% number of iterations
N=100;

% allocate (include n=0 so N+1 points)
x=zeros(1,N+1);
y=zeros(1,N+1);

% initial conditions (x0=y0=1)
x(1)=1;
y(1)=1;

% update functions
f = @(x,y) a1*x + r1*y;
g = @(x,y) a2*y + r2*x;

% iterate
n=1;
while n<=N
    x(n+1)=f(x(n),y(n));
    y(n+1)=g(x(n),y(n));
    n=n+1;
end

% time index n = 0,...,N
nvec=0:N;

% plot x_n and y_n vs n
plot(nvec,x,'o-')
hold on
plot(nvec,y,'o-')
xlabel('n')
ylabel('x_n, y_n')
legend('x_n','y_n')
set(gca,'fontsize',16)
set(gca,'fontweight','bold')