function [K,F] = petrov_galerkin(conn,problem,form)

% Petrov-Galerkin formulation of the weak form of
% a*u_x - nu*u_xx = 0
% Dirichlet boundary conditions are applied
% Hence boundary terms are neglected
% 'W_Star' is the added stability term in the formulation
% Integration of [W + W_star][a*u_x - nu*u_xx] = 0
% Higher order terms from the above equation have been neglected

%Problem information
nelem = problem.nelem;
nodes = problem.nodes;
a = problem.a;
alpha = problem.alpha;
nu = problem.nu;
h = problem.h;
ngaus = form.ngaus;
N = form.N;
dN = form.dN;
w = form.w;

K = zeros(nodes);
F = zeros(nodes,1);
for i=1:nelem            % Loop on elements
    conn_e = conn(i,:);
    Ke = zeros(2);
    for j=1:ngaus        % Loop on gauss points
       W_star = alpha*h/2*dN(:,j);
       Ke = Ke + h/2*w(j)*a*N(:,j)*dN(:,j)' + w(j)*nu*dN(:,j)*dN(:,j)'*...
           h/2 + w(j)*a*h/2*W_star*dN(:,j)';
    end
    % F remains a zero column matrix since there is no source
    % Global assembly of K matrix    
    K(conn_e,conn_e) = K(conn_e,conn_e) + Ke;
end

end

