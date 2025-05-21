class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __repr__(self):
        return f"Node({self.char}, {self.freq})"

def build_huffman_tree(freq_map):
    # Create initial list of nodes
    nodes = [Node(char, freq) for char, freq in freq_map.items()]
    
    # Sort nodes by frequency
    nodes.sort(key=lambda node: node.freq)

    while len(nodes) > 1:
        # Pick two nodes with smallest frequency
        left = nodes.pop(0)
        right = nodes.pop(0)

        # Create a new internal node with these two as children
        merged = Node(None, left.freq + right.freq)
        merged.left = left
        merged.right = right

        # Insert the new node back into the list and keep it sorted
        nodes.append(merged)
        nodes.sort(key=lambda node: node.freq)

    return nodes[0]  # Root of the tree

def generate_codes(node, prefix="", code_map={}):
    if node is None:
        return
    if node.char is not None:
        code_map[node.char] = prefix
    generate_codes(node.left, prefix + "0", code_map)
    generate_codes(node.right, prefix + "1", code_map)
    return code_map

# Example usage:
if __name__ == "__main__":
    text = "huffman coding without heap"
    
    # Build frequency map
    freq_map = {}
    for char in text:
        freq_map[char] = freq_map.get(char, 0) + 1

    # Build Huffman tree
    root = build_huffman_tree(freq_map)

    # Generate Huffman codes
    codes = generate_codes(root)

    # Print the codes
    print("Huffman Codes:")
    for char, code in codes.items():
        print(f"'{char}': {code}")

    # Encode the text
    encoded = ''.join(codes[char] for char in text)
    print("\nEncoded text:")
    print(encoded)
