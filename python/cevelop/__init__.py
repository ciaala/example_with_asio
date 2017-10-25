''' Minted Cevelop style
This style approximates the default highlighting style of Cevelop
'''
from pygments.style import Style
from pygments.token import Comment, Keyword, Name, String


class CevelopStyle(Style):
    background_color = '#fff'
    default_style = ''

    BOLD = 'bold '

    BLACK = '#000'
    BLUE = '#2a00ff'
    GREEN = '#3f7f5f'
    PURPLE = '#7f0055'

    styles = {
        Comment: GREEN,
        Comment.Preproc: BOLD + PURPLE,
        Comment.PreprocFile: BLUE,

        Keyword: PURPLE,

        Name.Function: BOLD + BLACK,

        String: BLUE,
    }
