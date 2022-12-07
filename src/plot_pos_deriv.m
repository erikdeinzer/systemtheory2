% Plots the position signal and its derivative
% Inputs:
%   pos: position signal (usually out.pos)
%   deriv: derivative of position signal (usually out.deriv)
%   norm_deriv_y: maximum y value on axis of derivative plot
%   name: "plus" or "minus" torque value -> e.g. "plus20" or "minus5"
function p = plot_pos_deriv(pos, deriv, norm_deriv_y, name)
    p = tiledlayout(2,1);

    %Plot Position
    nexttile
    plot(pos)
    title('Position Signal')
    ylabel('Position [°]') 
    yticks([0 45 90 135 180 225 270 315 360])
<<<<<<< HEAD
    axis([0 5 0 360])
=======
    axis([0 10 0 360])
    grid on
>>>>>>> f2cca4110adecc263b242f63c3446cac0dc67529

    %Plot Derivate
    nexttile
    plot(deriv)
    title('Derivative of Position')
    ylabel('')
<<<<<<< HEAD
    axis([0 5 -norm_deriv_y norm_deriv_y])
    
=======
    axis([0 10 -norm_deriv_y norm_deriv_y])
    grid on

>>>>>>> f2cca4110adecc263b242f63c3446cac0dc67529
    exportgraphics(p, join(['../plots/','ex_202_', name, '.jpg']))
end
