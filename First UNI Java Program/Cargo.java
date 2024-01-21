package CSC275;

import java.util.Scanner;

public class Cargo {
	Scanner input = new Scanner(System.in);

	public static void main(String[] args) {
		new Cargo();
	}

	// This will act as our program switchboard
	public Cargo() {
		String[] cargohold = new String[25];
		for (int i = 0; i < cargohold.length; i++) {
			cargohold[i] = "{empty}";
		}
		System.out.println("Welcome to the BlackStar Cargo Hold interface.");
		System.out.println("Please select a number from the options below");
		System.out.println("");

		while (true) {
			// Give the user a list of their options
			System.out.println("1: Add items to the cargo hold.");
			System.out.println("2: Remove an item from the cargo hold.");
			System.out.println("3: Sort the contents of the cargo hold.");
			System.out.println("4: Search for an item.");
			System.out.println("5: Display the items in the cargo hold.");
			System.out.println("0: Exit the BlackStar Cargo Hold interface.");

			// Get the user input
			int userChoice = input.nextInt();
			input.nextLine();

			switch (userChoice) {
			case 1:
				addItem(cargohold);
				break;
			case 2:
				removeItem(cargohold);
				break;
			case 3:
				sortItems(cargohold);
				break;
			case 4:
				searchItems(cargohold);
				break;
			case 5:
				displayItems(cargohold);
				break;
			case 0:
				System.out.println("Thank you for using the BlackStar Cargo Hold interface. See you again soon!");
				System.exit(0);
			}
		}
	}

	private void addItem(String cargohold[]) {
		// Counts empty spaces
		int empty = 0;
		for (int i = 0; i < cargohold.length; i++) {
			if (cargohold[i].equals("{empty}")) {
				empty++;
			}
		}
		if (empty == 0) {
			System.out.println("You have no free space.");
			return;
		}
		System.out.println("You have " + empty + " space(s) available. Enter the number of items to add:");
		int num = Integer.parseInt(input.nextLine());
		if (num > empty) {
			System.out.println("That number is too large");
			return;
		}
		if (num == 0) {
			return;
		}
		System.out.println("Enter " + num + " items");
		// Enters items where array is null
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < cargohold.length; j++) {
				if (cargohold[j].equals("{empty}")) {
					cargohold[j] = input.nextLine();
					break;
				}
			}
		}
	}

	private void removeItem(String cargohold[]) {
		int full = 0;
		for (int i = 0; i < cargohold.length; i++) {
			if (!cargohold[i].equals("{empty}")) {
				full++;
			}
		}
		if (full == 0) {
			System.out.println("You have no items.");
			return;
		}
		System.out.println("Enter the item you'd like to remove.");
		String remove = input.nextLine();
		boolean found = false;
		for (int i = 0; i < cargohold.length; i++) {
			if (cargohold[i].equals(remove)) {
				cargohold[i] = "{empty}";
				found = true;
				break;
			}
		}
		if (found) {
			System.out.println(remove + " was removed.");
		} else {
			System.out.println("There was no " + remove + ".");
		}
	}

	private void sortItems(String cargohold[]) {
		// Selection or Insertion sorts
		// NOTE: Special care is needed when dealing with strings! research the
		// compareTo() method with strings
		int full = 0;
		for (int i = 0; i < cargohold.length; i++) {
			if (!cargohold[i].equals("{empty}")) {
				full++;
			}
		}
		if (full == 0) {
			System.out.println("You have no items.");
			return;
		}
		String temp;
		int min;
		for (int i = 0; i < cargohold.length - 1; i++) {
			min = i;
			int minval = 0;
			for (int j = i + 1; j < cargohold.length; j++) {
				if (cargohold[j].compareTo(cargohold[i]) < minval) {
					min = j;
					minval = cargohold[j].compareTo(cargohold[i]);
				}
			}
			temp = cargohold[i];
			cargohold[i] = cargohold[min];
			cargohold[min] = temp;
		}
	}

	private void searchItems(String cargohold[]) {
		int full = 0;
		for (int i = 0; i < cargohold.length; i++) {
			if (!cargohold[i].equals("{empty}")) {
				full++;
			}
		}
		if (full == 0) {
			System.out.println("You have no items.");
			return;
		}
		System.out.println("Enter an item to search for.");
		String search = input.nextLine();
		int location = -1;
		for (int i = 0; i < cargohold.length; i++) {
			if (cargohold[i].equals(search)) {
				location = i;
				break;
			}
		}
		if (location != -1) {
			System.out.println(search + " was found at index " + location + ".");
		} else {
			System.out.println("Could not find " + search + ".");
		}
	}

	private void displayItems(String cargohold[]) {
		// For example it should say
		// Food - 2
		// Water - 3
		// Ammunition - 5
		int full = 0;
		for (int i = 0; i < cargohold.length; i++) {
			if (!cargohold[i].equals("{empty}")) {
				full++;
			}
		}
		if (full == 0) {
			System.out.println("You have no items.");
			return;
		}
		String temp;
		int min;
		for (int i = 0; i < cargohold.length - 1; i++) {
			min = i;
			int minval = 0;
			for (int j = i + 1; j < cargohold.length; j++) {
				if (cargohold[j].compareTo(cargohold[i]) < minval) {
					min = j;
					minval = cargohold[j].compareTo(cargohold[i]);
				}
			}
			temp = cargohold[i];
			cargohold[i] = cargohold[min];
			cargohold[min] = temp;
		}
		String[] item = new String[25];
		int[] count = new int[25];
		for (int k = 0; k < cargohold.length; k++) {
			item[k] = "{empty}";
			count[k] = 0;
		}
		int i = 0;
		for (int n = 0; n < cargohold.length - 1; n++) {
			item[i] = cargohold[n];
			count[i]++;
			if (!(cargohold[n].equals(cargohold[n + 1]))) {
				i++;
			}
		}
		for (int j = 0; j < count.length; j++) {
			if (!item[j].equals("{empty}")) {
				System.out.println(item[j] + " - " + count[j]);
			}
		}
	}

}