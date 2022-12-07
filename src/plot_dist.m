function p = plot_dist(dist, norm_dist, name)
    p = tiledlayout(1,1);
    nexttile
    plot(dist)
    title('Disturbance: ' + name)
    ylabel('Torque')
    yticks(-20:2:20)
    xticks(0:0.5:10)
    axis([0 5 -norm_dist norm_dist])

    exportgraphics(p, join(['../plots/','ex_202_', name, '.jpg']))