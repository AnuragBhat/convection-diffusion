clc
clear all


%%
%DEFINING THE PARAMETERS
dom =[0,1];

fprintf('Please enter the number of elements (default:10)\n')
Nelem = input('Number of elements: '); %NUMBER OF ELEMENTS
if isempty(Nelem)
    Nelem = 10; 
end

h = (dom(2) - dom(1))/Nelem;           %STEP SIZE
L = dom(2) - dom(1);                   %TOTAL LENGTH OF DOMAIN  
fprintf('Please enter the Peclet number (default:10)\n')
Pe = input('Peclet Number: ');         %PECLET NUMBER 
if isempty(Pe)
    Pe = 10; 
end

fprintf('Please enter the value of diffusion coefficient (default:0.01)\n')
nu = input('Diffusion Coefficient: '); %DIFFUSION COEFFICIENT
if isempty(nu)
    nu = 0.01; 
end

% Pe = a*h/(2*nu);
a = Pe*2*nu/h;                         %DEFINING 'a' IN TERMS OF Pe NUMBER
alpha = coth(Pe)-1/Pe;                 %DEFINING ALPHA 
nodes = Nelem + 1;                     %DEFINING THE NUMBER OF NODES 
X = (dom(1):h:dom(2))';                %DEFINING COORDINATES 
Conn = [1:(nodes-1);2:nodes]';         %CONNECTIVITY MATRIX
%alpha =1;

%%
%INITIALIZING THE MATRICES
K = zeros(nodes,nodes);                
F = zeros(nodes,1);

%DEFINING DIRICHLET NODES
nodes_Dir = [1,nodes];

%%
fprintf('Select a Method \n [1] Galerkin Method\n [2] Petrov Galerkin Method\n [3] Compare both\n')
choice = input('Method = ');

if choice==1                           %GALERKIN METHOD (SEPERATE)
    Method = 'Galerkin';
    for i = 1:Nelem                    %LOOP OVER ELEMENTS
        T = Conn(i,:);
        K_i = ((a/2)*[-1 1;-1 1] + (nu/h)*[1 -1;-1 1]);
        K(T,T) = K(T,T) + K_i;         %ASSEMBLING THE MATRIX
    end
else if choice==2                      %PETROV-GALERKIN METHOD (SEPERATE)
        Method = 'Petrov-Galerkin';
    for i = 1:Nelem                    %LOOP OVER ELEMENTS  
        T = Conn(i,:);   
        St = (alpha*a/2)*[1 -1;-1 1];  %ADDED STABILIZATION
        K_i = ((a/2)*[-1 1;-1 1] + (nu/h)*[1 -1;-1 1] + St);
        K(T,T) = K(T,T) + K_i;         %ASSEMBLING THE MATRIX
    end
else if choice==3                      %COMPARING BOTH METHODS TOGETHER
        Method='Comparison';
        K_G = zeros(nodes,nodes);
        F_G = zeros(nodes,1);
        K_P = zeros(nodes,nodes);
        F_P = zeros(nodes,1);
    for i = 1:Nelem                    %LOOP OVER ELEMENTS
        T = Conn(i,:);
        K_i_G = ((a/2)*[-1 1;-1 1] + (nu/h)*[1 -1;-1 1]);
        K_G(T,T) = K_G(T,T) + K_i_G;   %GALERKIN MATRIX ASSEMBLY
        K_i_P = ((a/2)*[-1 1;-1 1] + (nu/h)*[1 -1;-1 1] + (alpha*a/2)*[1 -1;-1 1]);
        K_P(T,T) = K_P(T,T) + K_i_P;   %PETROV-GALERKIN MATRIX ASSEMBLY
    end
else        
    error('Please select a valid method');
    end
    end
end

%%
%DETERMINING SOLUTION
if choice==1||choice==2
    F = F - K(:,nodes_Dir)*[1;0];       %TAKING DIRICHLET TERMS TO THE FORCE MATRIX SIDE
    K_f = K(2:nodes-1,2:nodes-1);       %FINAL K MATRIX 
    F_f = F(2:nodes-1);                 %FINAL F MATRIX

    sol = K_f\F_f;                      %SOLUTION
    u = zeros(nodes,1);                 %INITIALIZING THE SCALAR VARIABLE 
    u([1;nodes]) = [1;0];               %IMPOSING DIRICHLET VALUES 
    u(2:nodes-1) = sol;
    U_max = max(u);                     %FOR POST-PROCESSING    

else if choice==3
    
    %SOLUTION FOR GALERKIN METHOD 
    F_G = F_G - K_G(:,nodes_Dir)*[1;0]; 
    K_G_f = K_G(2:nodes-1,2:nodes-1); 
    F_G_f = F_G(2:nodes-1); 

    sol_G = K_G_f\F_G_f;
    u_G = zeros(nodes,1); 
    u_G([1;nodes]) = [1;0];
    u_G(2:nodes-1) = sol_G;         
    
    %SOLUTION FOR PETROV-GALERKIN METHOD
    F_P = F_P - K_P(:,nodes_Dir)*[1;0]; 
    K_P_f = K_P(2:nodes-1,2:nodes-1); 
    F_P_f = F_P(2:nodes-1); 

    sol_P = K_P_f\F_P_f;
    u_P = zeros(nodes,1); 
    u_P([1;nodes]) = [1;0];
    u_P(2:nodes-1) = sol_P;
    U_3max = max(u_G);
else
   error('Please select a valid method'); 
    end
end

%%
%POST-PROCESSING

%EXACT SOLUTION
U_exact =   (1 - (exp(a*(X-L)/nu)))/(1-exp(-(a*L/nu)));

%PLOTTING GALERKIN OR PETROV-GALERKIN DEPENDING ON USER CHOICE
if choice==1||choice==2 
    plot(X,u,'r-o',X,U_exact,'k:','LineWidth',1,'MarkerSize',5)
    l = legend(Method,'exact','Location','northwest'); 
    set(l,'FontSize',11)
    set(gca, 'FontSize',11);
    axis([0,1,0,(1.25*U_max)]);
    xlabel('Domain Length'); ylabel('Scalar Variable');
    t = sprintf('Pe = %s',num2str(Pe));
    title(t) 
    hold on
end    

%PLOTTING BOTH METHODS SIMULTANOUSLY FOR COMPARISON
if choice ==3
    plot(X,u_G,'r-o',X,u_P,'b-o',X,U_exact,'k:','LineWidth',1,'MarkerSize',5)
    l = legend('Galerkin','Petrov-Galerkin','exact','Location','northwest'); 
    set(l,'FontSize',11)
    set(gca, 'FontSize',11);
    axis([0,1,0,(1.25*U_3max)]);
    xlabel('Domain Length'); ylabel('Scalar Variable');
    t = sprintf('Pe = %s',num2str(Pe));
    title(t) 
end
    
%  if choice==1||choice==2 
%     plot(X,u,'b-o','LineWidth',1,'MarkerSize',5)
%     l = legend('exact','Upwind','Petrov-Galerkin','Location','northwest'); 
%     set(l,'FontSize',11)
%     set(gca, 'FontSize',11);
%     axis([0,1,0,(1.25*U_max)]);
%     xlabel('Domain Length'); ylabel('Scalar Variable');
%     t = sprintf('Pe = %s',num2str(Pe));
%     title(t) 
%     hold on
% end      