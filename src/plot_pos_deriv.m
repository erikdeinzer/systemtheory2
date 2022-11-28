function p = plot_pos_deriv(pos, deriv, norm_deriv_y, name)
    p = tiledlayout(2,1)

    %Plot Position
    nexttile
    plot(pos)
    title('Position Signal')
    ylabel('Position [°]') 
    yticks([0 45 90 135 180 225 270 315 360])
    axis([0 10 0 360])

    %Plot Derivate
    nexttile
    plot(deriv)
    title('Derivative of Position')
    ylabel('')
    axis([0 10 -norm_deriv_y norm_deriv_y])

    exportgraphics(p, join(['../plots/','ex_202_', name, '.jpg']))
end

    
    
