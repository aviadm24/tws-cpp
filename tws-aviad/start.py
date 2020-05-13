import os
import subprocess
import PySimpleGUI as sg
import datetime as dt
import threading
import queue
import traceback
import argparse
import datetime

RUNTIME = 10
with open('update.txt', 'w') as file:
    file.write('')


def main(stock, amount):
    # for filename in os.listdir(os.path.dirname(os.getcwd())):
    #     if filename == 'Main.cpp':
    #         print(filename)
    #         proc = subprocess.Popen([filename])
    #         proc.wait()
    with open('data.txt', 'w') as file:
        file.write(stock+'\n'+str(amount))
        # file.writelines(str(amount))
    proc = subprocess.Popen('bin/Debug/./tws-aviad')
    proc.wait()



sg.change_look_and_feel('DarkAmber')	# Add a touch of color
# All the stuff inside your window.
# element.Widget = remi.gui.Slider(layout_orientation = remi.gui.Widget.LAYOUT_HORIZONTAL, default_value=element.DefaultValue, min=element.Range[0], max=element.Range[1],step=element.Resolution)
layout = [
            [sg.Text('Yosef TWS GUI')],
            [sg.Text('Platform'), sg.Checkbox('TWS', key='tws', default=True)],
            [sg.Input('QQQ', size=(20, 1), key='stock'),
             sg.Frame('Trail - Amount', [[
                 sg.Slider(range=(0.01, 0.05), resolution=0.01, orientation='v', size=(5, 20), default_value=0.02, key='trail'),
                 sg.Slider(range=(100, 1000), resolution=100, orientation='v', size=(5, 20), default_value=200, key='amount'),
                 ]])],
            [sg.Text('Enter delta time in minutes'), sg.Input('1', key='delta')],
            [sg.Button('Start')],
            [sg.Button('Update Stop'), sg.Button('Position zero')],
            [sg.ProgressBar(1, orientation='h', size=(20, 20), key='progress')],
            [sg.Button('Cancel')]
         ]

window = sg.Window('', layout)
progress_bar = window['progress']
while True:
    event, values = window.read()
    gui_queue = queue.Queue()
    if event == 'Start':
        stock, trail, amount, delta = values['stock'], values['trail'], values['amount'], values['delta']
        start_time = dt.datetime.now()
        #  https://github.com/PySimpleGUI/PySimpleGUI/blob/master/DemoPrograms/Demo_Multithreaded_Multiple_Threads.py
        thread_id = threading.Thread(
            target=main,
            args=(stock, amount),
            daemon=True)
        app = thread_id.start()

        # print(stock, trail, amount)
        # main(stock, trail, amount)
    if event == 'Update Stop':
        with open('update.txt', 'w') as file:
            file.write('update')
        # gui_queue.put('update2')
        # print("queue: ", gui_queue.get())
    if event == 'Position zero':
        with open('update.txt', 'w') as file:
            file.write('last_buy')
    if event in (None, 'Cancel'):  # if user closes window or clicks cancel
        try:
            #  https: // stackoverflow.com / questions / 42867933 / ib - api - python - sample -not -using - ibpy
            app.done = True
        except:
            pass
        finally:
            break



window.close()








