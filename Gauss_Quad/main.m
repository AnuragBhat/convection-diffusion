clc 
clear all

%%
%Defining the parameters
dom = [0,1]; %Domain

fprintf('Please enter the number of elements (default:10)\n')
nelem = input('Number of elements: '); %Number of elements
if isempty(nelem)
    nelem = 10; 
end
h = (dom(2)-dom(1))/nelem; %Step sise
L = dom(2)-dom(1); %Domain length

fprintf('Please enter the value of diffusion coefficient (default:0.01)\n')
nu = input('Diffusion Coefficient: '); %Diffusion coefficient
if isempty(nu)
    nu = 0.01; 
end

fprintf('Please enter the Peclet number (default:10)\n')
Pe = input('Peclet Number: ');         %Peclet number 
if isempty(Pe)
    Pe = 10; 
end

a = Pe*2*nu/h;         % Defining 'a' in terms of Peclet number
alpha = coth(Pe)-1/Pe; % Defining alpha
tau = alpha*h/(2*a);   % Stabilization parameter for SU method 
nodes = nelem+1;       % Defining the number of nodes
nodes_Dir = [1,nodes]; % Defining the dirichlet nodes
X = dom(1):h:dom(2);   % Defining coordinate matrix
conn = [(1:nodes-1);(2:nodes)]'; %Connectivity matrix

problem.nelem = nelem;
problem.h = h;
problem.a = a;
problem.nu = nu;
problem.nodes = nodes;
problem.alpha = alpha;
problem.tau = tau;

%SHAPE FUNCTIONS
weight = [1 1];             % Weights for gauss quadrature
xi = [-1/sqrt(3) 1/sqrt(3)];% Gauss quadrature values
N1 = (1-xi)/2;              % Shape functions
N2 = (1+xi)/2;                  
ngaus = 2;                  % Number of gauss points
N = [N1;N2];
dN = [-1/2 -1/2;1/2 1/2]*2/h;% Derivatives of shape functios wrt 'xi'

form.w = weight;
form.xi = xi;
form.ngaus = ngaus;
form.N = N;
form.dN = dN;

fprintf('Select a Method \n [1] Galerkin Method\n [2] Petrov Galerkin Method')
fprintf('\n [3] Streamline Upwind\n')
choice = input('Method = ');

%%
% Galerkin formulation
if choice==1                         
    Method = 'Galerkin';
    [K,F] = galerkin(conn,problem,form);
end

% Petrov-Galerkin formulation
if choice ==2
    Method = 'Petrov-Galerkin';
    [K,F] = petrov_galerkin(conn,problem,form);
end

%Streamline-Upwind formulation
if choice ==3
    Method = 'Streamline-Upwind';
    [K,F] = streamline_upwind(conn,problem,form);
end

%Solution
F = F - K(:,nodes_Dir)*[1;0];       %Taking dirichlet terms to the force matrix side
K_f = K(2:nodes-1,2:nodes-1);       %Final K matrix
F_f = F(2:nodes-1);                 %Final F matrix

sol = K_f\F_f;                      %Solution
u = zeros(nodes,1);                 %Initializing the scalar variable 
u([1;nodes]) = [1;0];               %Imposing dirichlet values
u(2:nodes-1) = sol;
U_max = max(u); 

% Exact solution
U_exact =   (1 - (exp(a*(X-L)/nu)))/(1-exp(-(a*L/nu)));

%%
%Plot
plot(X,u,'r-o',X,U_exact,'k:','LineWidth',1,'MarkerSize',5)
l = legend(Method,'exact','Location','northwest'); 
set(l,'FontSize',11)
set(gca, 'FontSize',11);
axis([0,1,0,(1.25*U_max)]);
xlabel('Domain Length'); ylabel('Scalar Variable');
t = sprintf('Pe = %s',num2str(Pe));
title(t) 
hold on




