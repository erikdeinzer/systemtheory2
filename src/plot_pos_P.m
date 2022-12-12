function p = plot_pos_P(pos, pvalue, grad)
    p = tiledlayout(1,1);

    %Plot Position
    nexttile
    plot(pos)
    yline(grad, "-", 'Führungsgröße')
    str = join(['P-Regler = ', pvalue, ' Dauerschwingen   Führungsgröße: ', string(grad), '°']);
    title(str)
    ylabel('Position [°]') 
    yticks([0 45 90 135 180 225 270 315 360])
    axis([0 20 0 360])
    grid on
    exportgraphics(p, join(['../plots/Aufgabe3/','ex_301_P_Regler_Dauerschwingen_', pvalue, '_', string(grad), '.jpg']))
end

