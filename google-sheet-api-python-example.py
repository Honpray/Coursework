from __future__ import print_function
from googleapiclient.discovery import build
from httplib2 import Http
from oauth2client import file, client, tools

# If modifying these scopes, delete the file token.json.
SCOPES = 'https://www.googleapis.com/auth/spreadsheets'

# The ID and range of a sample spreadsheet.
spreadsheet_id = '18oxkrFKQqETnOmNAx0y2SrPGH0LMOrvVZQsFpxPvKO8'
range_name = 'Sheet1!A1:A2'
value_input_option = 'RAW'

def update_values(_service, spreadsheet_id, range_name, value_input_option, _values):
    """Write single cell using Sheets API.
    """
    service = _service
    values = [
        [
            # Cell values ... 
        ],
        # Additional rows ...
    ]
    values = _values
    body = {
        'values': values
    }
    result = service.spreadsheets().values().update(
                spreadsheetId=spreadsheet_id, range=range_name,
                    valueInputOption=value_input_option, body=body
            ).execute()
    print('{0} cells updated.'.format(result.get('updatedCells')));
    return result

def main():
    """Shows basic usage of the Sheets API.
    Prints values from a sample spreadsheet.
    """
    # Check credentials
    store = file.Storage('token.json')
    creds = store.get()
    if not creds or creds.invalid:
        flow = client.flow_from_clientsecrets('credentials.json', SCOPES)
        creds = tools.run_flow(flow, store)
    service = build('sheets', 'v4', http=creds.authorize(Http()))

    # Call the Sheets write API
    cellinput = [['hellosheet'],['helloagain']]
    update_values(service, spreadsheet_id, range_name, value_input_option, cellinput)
    
if __name__ == '__main__':
    main()
