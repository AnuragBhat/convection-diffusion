clc
clear all
%%
%IMPORTING DATA
Res = importdata('Result.dat');
A = Res.data;

u = A(:,1);       %SOLUTION
U_exact = A(:,2); %EXACT SOLUTION
X = A(:,3);       %COORDINATE
U_max = max(u);
Method = 'Solution';
%%
%PLOTTING THE RESULT
plot(X,u,'r-o',X,U_exact,'k:','LineWidth',1,'MarkerSize',5)
l = legend(Method,'exact','Location','northwest'); 
set(l,'FontSize',11)
set(gca, 'FontSize',11);
axis([0,1,0,(1.25*U_max)]);
xlabel('Domain Length'); ylabel('Scalar Variable');
hold on




