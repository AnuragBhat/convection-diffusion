function [K,F] = galerkin(conn,problem,form)

% Galerkin formulation of the weak form of
% a*u_x - nu*u_xx = 0
% Dirichlet boundary conditions are applied
% Hence boundary terms are neglected

%Problem information
nelem = problem.nelem;
nodes = problem.nodes;
a = problem.a;
nu = problem.nu;
h = problem.h;
w = form.w;
ngaus = form.ngaus;
N = form.N;
dN = form.dN;

K = zeros(nodes);
F = zeros(nodes,1);
for i=1:nelem           % Loop on elements
    conn_e = conn(i,:);
    Ke = zeros(2);
    for j=1:ngaus       % Loop on gauss points
       Ke = Ke + h/2*w(j)*a*N(:,j)*dN(:,j)' + w(j)*nu*dN(:,j)*dN(:,j)'*h/2;
    end
    % F remains a zero column matrix since there is no source
    % Global assembly of K matrix
    K(conn_e,conn_e) = K(conn_e,conn_e) + Ke;
end

end