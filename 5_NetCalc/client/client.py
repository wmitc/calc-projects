import argparse
import os
import socket
import struct

DEFAULT_IP = "127.0.0.1"
DEFAULT_PORT = 31337
NET_HDR_SZ = 48
NET_FNAME_MAX = 24
NET_NAME_FIELD_SZ = 32

def recv_all(sock, num_bytes):
    '''
    Recive function to handle partial receives

    Args:
        sock: socket
        num_bytes: expected number of bytes to receive
    
    Returns:
        bytes: Data received
    '''
    data = b""
    while len(data) < num_bytes:
        chunk = sock.recv(num_bytes - len(data))
        if not chunk:
            raise ConnectionError("Connection closed prematurely.")
        data += chunk
    return data

def gen_net_header(pkt_len, efile_name_len, efile_name):
    '''
    Generates network header based on project specification.

    Args:
        pkt_len (int): length of packet
        efile_name_len (int): length of file
        efile_name (string): name of file

    Returns:
        string: A network header based on the provided parameters
    '''
    hdr_len = NET_HDR_SZ
    filename_len = efile_name_len
    pkt_len = pkt_len + NET_HDR_SZ
    filename = efile_name.ljust(NET_NAME_FIELD_SZ, "\x00")
    print(hdr_len, filename_len, pkt_len, filename)
    hdr = struct.pack("!IIQ", hdr_len, filename_len, pkt_len)
    hdr += filename.encode('utf-8')

    #print(hdr)

    return hdr

def get_files_from_dir(dir):
    '''
    Get files from a directory

    Args:
        dir (string): directory from which to list files

    Returns:
        files (list): list of filenames 
    '''
    files = os.listdir(dir)
    return files

def client(args):
    '''
    Connects to the server and sends file content from input 
    directory files for processing. Retrieves server responses 
    and stores them in new files in the output directory.

    Args:
        args (ArgumentParser): object containing CLI-request parameters
    '''
    # Extract host and port from args
    host = args.s
    port = args.p


    ''' Options:
    
    1. Send input_dir and output_dir to server? --> no
    2. Read files and send data to server? *** --> YES
    
    Okay, need to to read files from indir and
    send send data to the server with the additional 
    header info. The server reads the header info 
    
    '''
    
    # Retrieve file based on input directory
    files = get_files_from_dir(args.i)

    # Iterate over the files
    for file in files:
        # Instantiate new socket for each file
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Connect to server
        client_socket.connect((host, port))

        # Get path of output directory + filename
        in_path = args.i + "/" + file
        out_path = args.o + "/" + file

        # Open each input file
        with open(in_path, 'rb') as f:
            file_data = f.read()

            header = gen_net_header(len(file_data), len(file), file)

            packet = header + file_data
  
            ### Okay packet construction looks good!
            print(len(packet))
            
            # Send packet to server
            client_socket.sendall(packet)
            print(f"[+] Sent {file} to server.")

            # Recv data back; check header first
            recv_header = recv_all(client_socket, len(header))
            if(header != recv_header):
                print("[-] Unexpected file header received from server.")
                print("Sent header: ", header)
                print()
                print("Recv header: ", recv_header)
                break

            # If headers match, recv remaining data
            data = client_socket.recv(len(file_data))

            # Write results into output file
            with open(out_path, 'wb') as f:
                f.write(data)
                print(f"[+] Wrote solutions to {out_path}.")

        # Close socket
        client_socket.close()

def parse():
    '''
    Parses command line input.

    Args:
        None

    Returns: 
        ArgumentParser object containing request parameters.
    '''
    # Set up argument parser
    parser = argparse.ArgumentParser(description="NetCalc - File parsing over the network.")

    # Add all arguments
    parser.add_argument("-s", help="IP address of server; default to 127.0.0.1")
    parser.add_argument("-p", type=int, help="port to connect to; defaults to 31337")
    parser.add_argument("-i", help="folder of unsolved EQU", required=True)
    parser.add_argument("-o", help="folder of solved EQU", required=True)

    # Get command line input
    args = parser.parse_args()
    
    # Set IP to default if not specified
    if(not args.s):
       args.s = DEFAULT_IP

    # Set default port if not specified
    if(not args.p):
        args.p = DEFAULT_PORT
    
    return args

if __name__ == "__main__":
    args = parse()
    client(args)
    
