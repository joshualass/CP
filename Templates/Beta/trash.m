// % 1. Define the time span for the plot
// t = linspace(0, 5, 500); % t goes from 0 to 5, which is plenty for e^(-2t) to settle

// % 2. Define the initial conditions requested
// x0_values = [-3, -1, 1, 3];

// % 3. Define the steady state solutions
// steady_states = [-sqrt(3), 0, sqrt(3)]; 

// % Set up the figure
// figure;
// hold on;

// % 4. Loop through each initial condition and plot the curve
// colors = lines(length(x0_values)); % Get distinct colors

// for i = 1:length(x0_values)
//     x0 = x0_values(i);
    
//     % Evaluate the correct equation based on |x0| compared to sqrt(3)
//     if abs(x0) < sqrt(3)
//         % Equation for |x0| < sqrt(3)
//         % Note the use of ./ since we are dividing a scalar by a vector (t)
//         x_t = sign(x0) * sqrt(3 ./ (1 + ((3 - x0^2) / x0^2) * exp(-2*t)));
        
//     elseif abs(x0) > sqrt(3)
//         % Equation for |x0| > sqrt(3)
//         x_t = sign(x0) * sqrt(3 ./ (1 - ((x0^2 - 3) / x0^2) * exp(-2*t)));
        
//     else
//         % If x0 is exactly a steady state like +/- sqrt(3)
//         x_t = x0 * ones(size(t));
//     end
    
//     % Plot the curve
//     plot(t, x_t, 'Color', colors(i,:), 'LineWidth', 1.5, ...
//          'DisplayName', sprintf('x_0 = %d', x0));
// end

// % 5. Plot the steady state solutions as dashed lines
// for i = 1:length(steady_states)
//     ss = steady_states(i);
//     yline(ss, '--k', 'LineWidth', 1.5, ...
//           'DisplayName', sprintf('Steady State x = %.3g', ss));
// end

// % 6. Format the graph to make it clean and readable
// xlabel('t');
// ylabel('x');
// title('x v t');
// grid on;
// hold off;

// % 1. Define the range for x
// % x from 0 to 4 will clearly show the intersections for these m values
// x = linspace(0, 4, 500);

// % 2. Define the first function (the Hill function part with c=2)
// % Remember to use element-wise operations (.^ and ./)
// y_hill = (x.^2) ./ (1 + x.^2);

// % 3. Define the slope values (m) for the linear functions
// m_values = [0.4, 0.45, 0.5, 0.55];

// % Set up the figure
// figure;
// hold on;

// % 4. Plot the Hill function curve
// plot(x, y_hill, 'k-', 'LineWidth', 2, 'DisplayName', 'x^2 / (1 + x^2)');

// % 5. Loop through each m value and plot the corresponding line mx
// colors = lines(length(m_values)); % Get distinct colors for the lines
// for i = 1:length(m_values)
//     m = m_values(i);
//     y_line = m * x;
    
//     % Plot the line
//     plot(x, y_line, 'Color', colors(i,:), 'LineWidth', 1.5, ...
//          'DisplayName', sprintf('m = %g', m));
// end

// % 6. Format the graph to make it clean and readable
// xlabel('x');
// ylabel('Function Value');
// title('Intersection of Hill Function and mx');
// legend('Location', 'best');
// grid on;
// hold off;

% 1. Define the range for x
% x from 0 to 4 will clearly show the intersections for these m values
x = linspace(0, 4, 500);

% 2. Define the first function (the Hill function part with c=2)
% Remember to use element-wise operations (.^ and ./)
y_hill = (x.^2) ./ (1 + x.^2);

% 3. Define the slope values (m) for the linear functions
m_values = [0.4, 0.45, 0.5, 0.55];

% Set up the figure
figure;
hold on;

% 4. Plot the Hill function curve
plot(x, y_hill, 'k-', 'LineWidth', 2, 'DisplayName', 'x^2 / (1 + x^2)');

% 5. Loop through each m value and plot the corresponding line mx
colors = lines(length(m_values)); % Get distinct colors for the lines
for i = 1:length(m_values)
    m = m_values(i);
    y_line = m * x;
    
    % Plot the line
    plot(x, y_line, 'Color', colors(i,:), 'LineWidth', 1.5, ...
         'DisplayName', sprintf('m = %g', m));
end

% 6. Format the graph to make it clean and readable
xlabel('x');
ylabel('f(x)');
title('Plot with functions and slopes');
legend('Location', 'best');
grid on;
hold off;