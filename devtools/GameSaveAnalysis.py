import matplotlib.pyplot as plt

def read_data(file_path):
    """
    Read data from a file and return the x and y values.

    Args:
        file_path (str): The path to the data file.

    Returns:
        tuple: A tuple containing the x and y values. If the file is not found or has invalid data, returns empty lists.
    """
    with open(file_path, 'r') as file:
        lines = file.readlines()
        if len(lines) >= 3:
            data_line = lines[2].strip()
            if data_line.endswith('-1'):
                data_values = [float(val) for val in data_line[:-2].split()]  # Remove the '-1' terminator
                x = list(range(1, len(data_values) + 1))
                return x, data_values
    return [], []

def get_user_input():
    """
    Prompt the user to enter file numbers and validate the input.

    Returns:
        list: A list of selected file numbers.
    """
    print("Enter the file numbers you want to display (0-19), separated by spaces:")
    user_input = input().strip()
    try:
        file_numbers = [int(num) for num in user_input.split() if 0 <= int(num) <= 19]
        return file_numbers
    except ValueError:
        print("Invalid input. Please enter numbers between 0 and 19.")
        return get_user_input()

def get_graph_type():
    """
    Prompt the user to choose between percentage change or absolute value graph.

    Returns:
        str: The chosen graph type ('pct' for percentage change, 'abs' for absolute value).
    """
    print("Do you want to show percentage change or absolute value graph?")
    print("Enter 'pct' for percentage change or 'abs' for absolute value:")
    graph_type = input().strip().lower()
    if graph_type == 'pct':
        return 'pct'
    elif graph_type == 'abs':
        return 'abs'
    else:
        print("Invalid input. Please enter 'pct' or 'abs'.")
        return get_graph_type()

# Get user input for file selection
selected_files = get_user_input()

# Get user input for graph type
graph_type = get_graph_type()

data = []

for file_num in selected_files:
    file_path = f"saves/save/{file_num}.save"
    try:
        x, y = read_data(file_path)
        if x and y:  # Only add if we have data
            if graph_type == 'pct':
                percentage_changes = []
                for i in range(1, len(y)):
                    if y[i-1] != 0:  # Avoid division by zero
                        pct_change = ((y[i] - y[i-1]) / y[i-1]) * 100
                    else:
                        pct_change = 0  # or float('inf') if you prefer
                    percentage_changes.append(pct_change)
                data.append((x[:-1], percentage_changes, file_num))  # Exclude the last index for pct_change
            else:
                data.append((x, y, file_num))
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"Error reading {file_path}: {e}")

if not data:
    print("No valid data to plot.")
else:
    fig, ax = plt.subplots(figsize=(10, 6))

    for x, y, file_num in data:
        ax.plot(x, y, label=f"File {file_num}")

    if graph_type == 'pct':
        graph_title = "Percentage Change of Values from Selected Data Files"
        y_label = "Percentage Change (%)"
    else:
        graph_title = "Absolute Values from Selected Data Files"
        y_label = "Value"

    ax.set_title(graph_title)
    ax.set_xlabel("Index")
    ax.set_ylabel(y_label)
    ax.legend()
    plt.grid(True)
    plt.show()
