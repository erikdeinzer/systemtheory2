function p = plot_pos_PI(pos, pvalue, ivalue, grad)
    p = tiledlayout(1,1);

    %Plot Position
    nexttile
    plot(pos)
    yline(grad, "-", 'Führungsgröße')
    str = join(['PI-Regler : K = ', pvalue, ' T_I = ',ivalue, '   Führungsgröße: ', string(grad), '°']);
    title(str)
    ylabel('Position [°]') 
    yticks([0 45 90 135 180 225 270 315 360])
    axis([0 5 0 360])
    grid on
    exportgraphics(p, join(['../plots/Aufgabe3/','ex_301_PI_Regler_', pvalue, '_', ivalue, '_', string(grad), '.jpg']))
end