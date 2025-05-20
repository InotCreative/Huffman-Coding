# Define a node for Huffman Tree
class Node:
    def __init__(self, char=None, count=0, left=None, right=None):
        self.char = char       # Character (None if internal node)
        self.count = count     # Frequency count
        self.left = left       # Left child
        self.right = right     # Right child

def build_huffman_tree(char_counts):
    # char_counts is a list of (char, count) tuples

    # Step 1: Create a list of Nodes for each character
    nodes = [Node(char=c, count=f) for c, f in char_counts]

    # Step 2: Sort nodes by count
    nodes.sort(key=lambda node: node.count)

    # Step 3: Repeat until one node remains
    while len(nodes) > 1:
        # Take two nodes with smallest counts (front of list)
        left = nodes.pop(0)
        right = nodes.pop(0)

        # Create a new internal node with combined count
        merged = Node(char=None, count=left.count + right.count, left=left, right=right)

        # Insert the new node back into the list to keep sorted order
        # Find position to insert
        inserted = False
        for i in range(len(nodes)):
            if nodes[i].count >= merged.count:
                nodes.insert(i, merged)
                inserted = True
                break
        if not inserted:
            nodes.append(merged)

    # The last node is the root of Huffman tree
    return nodes[0]

# Example usage:
char_counts = [
    ('L', 1), ('U', 1), ('D', 1), ('h', 1), ('E', 1),
    ('g', 3), ('b', 3), (' ', 3), ('v', 3), ('x', 3), ('f', 3),
    ('.', 4), (',', 4), ('q', 5), ('p', 11), ('c', 16), ('m', 17),
    ('s', 18), ('d', 18), ('l', 21), ('r', 22), ('n', 24), ('u', 28),
    ('a', 29), ('o', 29), ('t', 32), ('e', 37), ('i', 42), (' ', 65)
]

root = build_huffman_tree(char_counts)

def print_node(node):
    if node is None:
        print("Empty node")
        return
    
    if node.char is None:
        print(f"Root node: Internal node with count = {node.count}")
    else:
        print(f"Root node: Leaf node with character = '{node.char}' and count = {node.count}")

# Assuming 'root' is the tree root from the previous code:
def generate_codes(node, prefix="", codebook=None):
    if codebook is None:
        codebook = {}

    if node.char is not None:
        # Leaf node: assign the prefix as the code for this character
        codebook[node.char] = prefix
    else:
        # Internal node: recurse left and right with updated prefix
        if node.left:
            generate_codes(node.left, prefix + "0", codebook)
        if node.right:
            generate_codes(node.right, prefix + "1", codebook)
    return codebook

# Using your Huffman tree root:
codes = generate_codes(root)

# Print the codes
for char, code in codes.items():
    if char == " ":
        print(f"'space': {code}")
    else:
        print(f"'{char}': {code}")
