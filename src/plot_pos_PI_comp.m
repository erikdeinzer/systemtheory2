function p = plot_pos_PI_comp(pos, noisetype)
    p = tiledlayout(1,1);

    %Plot Position
    nexttile
    plot(pos)
    yline(200, "-", 'Führungsgröße')
    str = join(['TYPE: ',noisetype,'(komp) | PI-Regler: K = 0.765, T_I = 0.392    Führungsgröße: 200 °']);
    title(str)
    ylabel('Position [°]') 
    yticks([0 45 90 135 180 225 270 315 360])
    axis([0 5 0 360])
    grid on
    exportgraphics(p, join(['../plots/Aufgabe4/','ex_4_PI_Regler_Type_comp_', noisetype, '.jpg']))
end